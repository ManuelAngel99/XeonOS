/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-19 16:20:32
* 
* File: physical_memory.c
* Description: Some routines to manage physical memory
*/

#include <arch/x86/physical_memory.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

static memory_map_t physical_memory;

static int32_t physical_memory_find_first_free_block(void);
static int32_t physical_memory_find_first_free_chain(uint32_t chain_size);
static bool physical_memory_map_check_if_used(uint32_t starting_bit, uint32_t count);
inline static void physical_memory_map_set_free(uint32_t bit, uint32_t* target);
inline static void physical_memory_map_set_used(uint32_t bit, uint32_t* target);
static void physical_memory_update_bitmaps(uint32_t reference_block);

inline static void physical_memory_map_set_used(uint32_t bit, uint32_t* target)
{
	target[ bit / LEVEL_MULTIPLICATOR  ] |= (1 << (bit % LEVEL_MULTIPLICATOR ) );
}

inline static void physical_memory_map_set_free(uint32_t bit, uint32_t* target)
{
	target[ bit / LEVEL_MULTIPLICATOR  ] &= ~(1 << (bit % LEVEL_MULTIPLICATOR ) );
}

static bool physical_memory_map_check_if_used(uint32_t starting_bit, uint32_t count)
{
	if( ( LEVEL_MULTIPLICATOR  - ((int32_t)starting_bit%32 + (int32_t)count) ) < 0)
        return (__builtin_ctz(physical_memory.blocks[starting_bit/ LEVEL_MULTIPLICATOR  +1]) + __builtin_clz(physical_memory.blocks[starting_bit/ LEVEL_MULTIPLICATOR ])) < (int32_t)count;
        
    return ( physical_memory.blocks[starting_bit/ LEVEL_MULTIPLICATOR ] & ( ((1<<(count)) -1) << starting_bit % LEVEL_MULTIPLICATOR ) ) != 0;
}

static int32_t physical_memory_find_first_free_block(void)
{
    uint32_t a, b, c, d, j, buffer = 0;
    for( a = 0; a <= physical_memory.total_hyper_blocks; a++)
        if(physical_memory.hyper_blocks[a] != 0xFFFFFFFF)
            for( b = a * LEVEL_MULTIPLICATOR ; b <= physical_memory.total_mega_blocks; b++)
                if(physical_memory.mega_blocks[b] != 0xFFFFFFFF)
                    for( c = b * LEVEL_MULTIPLICATOR ; c <= physical_memory.total_super_blocks; c++)
                        if(physical_memory.super_blocks[c] != 0xFFFFFFFF)
                            for ( d = c * LEVEL_MULTIPLICATOR ; d < physical_memory.total_blocks; d++)
                                if(physical_memory.blocks[d] != 0xFFFFFFFF)								// If there is a free bit	
                                {
                                    buffer = ~physical_memory.blocks[d] & (physical_memory.blocks[d]+1);	// Isolate the first free bit
                                        for(j = 0; buffer !=1; j++)
                                            buffer = buffer >> 1;								// Right shift buffer until it's 0
                                    return ( d * LEVEL_MULTIPLICATOR  + j);
                                }
                        
    return -1;
}

static int32_t physical_memory_find_first_free_chain(uint32_t chain_size)
{
    uint32_t starting_block, a, b, c, d, j;
    
	if( chain_size == 0)                                                                                // You cannot allocate 0 pages!
		return -1;
	else if(chain_size == 1)                                                                            // Use the find first free block method
		return physical_memory_find_first_free_block();
    
    for( a = 0; a <= physical_memory.total_hyper_blocks; a++)
        if(physical_memory.hyper_blocks[a] != 0xFFFFFFFF)
            for( b = a * LEVEL_MULTIPLICATOR ; b <= physical_memory.total_mega_blocks; b++)
                if(physical_memory.mega_blocks[b] != 0xFFFFFFFF)
                    for( c = b * LEVEL_MULTIPLICATOR ; c <= physical_memory.total_super_blocks; c++)
                        if(physical_memory.super_blocks[c] != 0xFFFFFFFF)
                            for ( d = c * LEVEL_MULTIPLICATOR ; d < physical_memory.total_blocks; d++)
                                if(physical_memory.blocks[d] != 0xFFFFFFFF)								// If there is a free bit	
                                {
                                    for(j = 0; j < LEVEL_MULTIPLICATOR ; j++)                                             //Test every bit                              
                                    {
                                        starting_block = LEVEL_MULTIPLICATOR *d + j;
                                        if(!physical_memory_map_check_if_used(starting_block, chain_size))
                                            return starting_block;
                                    }

                                }
                                
	return -1;
}

static void physical_memory_update_bitmaps(uint32_t reference_block)
{
	uint32_t index = reference_block / LEVEL_MULTIPLICATOR;
	if(physical_memory.blocks[index] == 0xFFFFFFFF)
		physical_memory_map_set_used( index / LEVEL_MULTIPLICATOR, physical_memory.super_blocks );
	else
		physical_memory_map_set_free( index / LEVEL_MULTIPLICATOR, physical_memory.super_blocks );

	if(physical_memory.super_blocks[ index / LEVEL_MULTIPLICATOR ] == 0xFFFFFFFF)
		physical_memory_map_set_used( index / DOUBLE_LEVEL_MULTIPLICATOR, physical_memory.mega_blocks);
	else
		physical_memory_map_set_free( index / DOUBLE_LEVEL_MULTIPLICATOR, physical_memory.mega_blocks);

	if (physical_memory.mega_blocks[index / DOUBLE_LEVEL_MULTIPLICATOR] == 0xFFFFFFFF)
		physical_memory_map_set_used(index / TRIPLE_LEVEL_MULTIPLICATOR, physical_memory.hyper_blocks);
	else
		physical_memory_map_set_free(index / TRIPLE_LEVEL_MULTIPLICATOR, physical_memory.hyper_blocks);
}

void setup_physical_memory_map(uint32_t total_kbytes, physical_address bitmaps_start)
{
	physical_memory.total_memory = total_kbytes;

	physical_memory.total_blocks = total_kbytes/4;
	physical_memory.total_super_blocks = physical_memory.total_blocks / LEVEL_MULTIPLICATOR ;
	physical_memory.total_mega_blocks = physical_memory.total_super_blocks / LEVEL_MULTIPLICATOR ;
	physical_memory.total_hyper_blocks = physical_memory.total_mega_blocks / LEVEL_MULTIPLICATOR ;
	physical_memory.used_blocks = physical_memory.total_blocks;

	physical_memory.blocks = (uint32_t*) bitmaps_start;
	physical_memory.super_blocks = (uint32_t*)( physical_memory.blocks + (uint32_t)physical_memory.blocks * sizeof(uint32_t));
	physical_memory.mega_blocks  = (uint32_t*)( physical_memory.super_blocks + (uint32_t)physical_memory.super_blocks * sizeof(uint32_t));
	physical_memory.hyper_blocks = (uint32_t*)( physical_memory.mega_blocks + (uint32_t)physical_memory.mega_blocks * sizeof(uint32_t));

	memset(physical_memory.blocks,       0xF, physical_memory.total_blocks);			//By default all memory is in use
	memset(physical_memory.super_blocks, 0xF, physical_memory.total_super_blocks);
	memset(physical_memory.mega_blocks,  0xF, physical_memory.total_mega_blocks);
	memset(physical_memory.hyper_blocks, 0xF, physical_memory.total_hyper_blocks);
}

void physical_memory_free_region(physical_address base, size_t size)
{
	if(size == 0)
		return;
	
	uint32_t align  = base / PHYSICAL_BLOCK_SIZE;

	for (uint32_t i = 0; i < (size/PHYSICAL_BLOCK_SIZE); i++, align++)
	{
		physical_memory_map_set_free(align, physical_memory.blocks);
		physical_memory.used_blocks--;

		if( i % 32 == 0)
			physical_memory_update_bitmaps( align );

	}

	physical_memory_map_set_used(0, physical_memory.blocks);
}

void physical_memory_alloc_region(physical_address base, size_t size)
{
	if(size == 0)
		return;

	uint32_t align  = base / PHYSICAL_BLOCK_SIZE;

	for (uint32_t i = 0; i < (size/PHYSICAL_BLOCK_SIZE); i++, align++)
	{
		physical_memory_map_set_used(align, physical_memory.blocks);
		physical_memory.used_blocks++;

		if( i % 32 == 0)
			physical_memory_update_bitmaps( align );
	}
}


void* physical_memory_alloc_block(void)
{
	if( physical_memory_get_free_block_count() > 1)
	{
		int frame = physical_memory_find_first_free_block();
		if(frame != -1)
		{
			physical_memory_map_set_used(frame, physical_memory.blocks);
			physical_memory.used_blocks++;
			physical_memory_update_bitmaps( frame );
			return ( (void*) (frame * PHYSICAL_BLOCK_SIZE ));
		}
	}
	return NULL;
}

void* physical_memory_alloc_blocks(size_t size)
{
	if( physical_memory_get_free_block_count() > size + 1)
	{
		int starting_frame = physical_memory_find_first_free_chain(size);
		if(starting_frame != -1)
		{
			physical_memory_alloc_region(starting_frame*PHYSICAL_BLOCK_SIZE, size);
			physical_memory.used_blocks++;

			return ((void*) (starting_frame * PHYSICAL_BLOCK_SIZE));
		}
	}

	return NULL;
}

void physical_memory_free_block(void* address)
{
	int frame = (physical_address)address / PHYSICAL_BLOCK_SIZE;
	physical_memory_map_set_free(frame, physical_memory.blocks);
	physical_memory.used_blocks--;
	physical_memory_update_bitmaps(frame);
}

void physical_memory_free_blocks(void* address, size_t size)
{
	physical_memory_free_region(address, size);
	physical_memory.used_blocks--;
}



size_t physical_memory_get_memory_size(void)
{
	return physical_memory.total_memory;
}

uint32_t physical_memory_get_block_count(void)
{
	return physical_memory.total_blocks;
}

uint32_t physical_memory_get_used_block_count(void)
{
	return physical_memory.used_blocks;
}

uint32_t physical_memory_get_free_block_count(void)
{
	return physical_memory.total_blocks - physical_memory.used_blocks;
}

uint32_t physical_memory_get_block_size(void)
{
	return PHYSICAL_BLOCK_SIZE;
}