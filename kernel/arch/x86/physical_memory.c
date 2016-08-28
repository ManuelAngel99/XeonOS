/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-19 16:20:32
* 
* File: physical_memory.c
* Description: Some routines to manage physical memory
*/

#include <arch/x86/physical_memory.h>
#include <arch/x86/multiboot.h>
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

void physical_memory_free_region(physical_address base, size_t size);
void physical_memory_alloc_region(physical_address base, size_t size);


static void setup_physical_memory_map(uint32_t total_kbytes, physical_address bitmaps_start)
{
	physical_memory.total_memory = total_kbytes;

	physical_memory.total_blocks = total_kbytes/4; //A page is 4kbytes
	physical_memory.used_blocks = physical_memory.total_blocks;

	physical_memory.blocks = (uint32_t*) bitmaps_start;

	memset(physical_memory.blocks,       0xF, physical_memory.total_blocks);			//By default all memory is in use
}

static uint32_t get_grub_total_kbytes_of_memory(multiboot_info_t* multiboot_pointer, uint32_t mem_upper)
{
	uint32_t total_kbytes = 0;
	multiboot_memory_map_t* grub_memory_map = (multiboot_memory_map_t*)multiboot_pointer->mmap_addr;
	while(grub_memory_map < (multiboot_memory_map_t*)(multiboot_pointer->mmap_addr + multiboot_pointer->mmap_length))
	{
		if(mem_upper == (uint32_t)(grub_memory_map->len)/1024)
		{
			 grub_memory_map = (multiboot_memory_map_t*) + ( (unsigned int)grub_memory_map + grub_memory_map->size + 4 );
			 total_kbytes = (grub_memory_map->addr + grub_memory_map->len) / 1024;
		}

	    grub_memory_map = (multiboot_memory_map_t*) + ( (unsigned int)grub_memory_map + grub_memory_map->size + 4 );
	}
	return total_kbytes;
}

void setup_pmm(multiboot_info_t* multiboot_pointer)
{
	multiboot_memory_map_t* grub_memory_map = (multiboot_memory_map_t*)multiboot_pointer->mmap_addr;
	physical_address bitmap_start = 0x3C00000;
	uint32_t total_kb = get_grub_total_kbytes_of_memory(multiboot_pointer, multiboot_pointer->mem_upper);

	setup_physical_memory_map(total_kb, bitmap_start);


	while(grub_memory_map < (multiboot_memory_map_t*)(multiboot_pointer->mmap_addr + multiboot_pointer->mmap_length))
	{

#ifdef NDEBUG
		printf("Base adresses %x ", (uint32_t)(grub_memory_map->addr)/1024);
		printf(",length %x ", (uint32_t)(grub_memory_map->len)/1024);
		printf(",memory type %x\n", grub_memory_map->type);
#endif // NDEBUG

		if(grub_memory_map->type == 1 && (grub_memory_map->addr/1024) > multiboot_pointer->mem_lower) //Free the avaliable regions of the memory except the low adressed
			physical_memory_free_region((physical_address)grub_memory_map->addr, (size_t)(grub_memory_map->len));

	    grub_memory_map = (multiboot_memory_map_t*) + ( (unsigned int)grub_memory_map + grub_memory_map->size + 4 );
	}

	//Alloc the kernel region
	physical_memory_alloc_region(0x0, 0x1000000);
#ifdef NDEBUG
	printf("TOTAL KB OF MEM: %x \n", total_kb);
	printf("BLOCKS TOTAL/USED: %d/%d\n",physical_memory.total_blocks, physical_memory.used_blocks);
#endif //NDEBUG
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

		if( align % 32 == 0)
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

		if( align % 32 == 0)
			physical_memory_update_bitmaps( align );
	}
}

inline static bool physical_memory_map_test(uint32_t bit)
{
	return physical_memory.blocks[bit/32] & (1 << bit % 32);
}


void print_frame(uint32_t frame)
{
	size_t i = frame / 32;
	for (size_t bit = 0; bit < 32; bit++)
	{
		printf("%d", physical_memory_map_test(i*32 + bit));
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
	if( physical_memory_get_free_block_count() > size )
	{
		int starting_frame = physical_memory_find_first_free_chain(size);
		printf("FRAME TO ALLOCATE: %d, expected end: %d\n", starting_frame, starting_frame + size);

		if(starting_frame != -1)
		{
			physical_memory_alloc_region(starting_frame*PHYSICAL_BLOCK_SIZE, size*PHYSICAL_BLOCK_SIZE);
			for(size_t k = 0; k < size ; k++)
			{
				if(physical_memory_map_test(starting_frame + k) != true)
				{
					printf("FATAL ERROR\n");
					break;
				}
			}

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
	physical_memory_free_region((physical_address)address, size);
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