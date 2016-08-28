/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-19 16:20:45
* 
* File: physical_memory.h
* Description: Definitions for physical memory managment
*/


#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include <arch/x86/multiboot.h>
#include <bitmap.h>
#include <stdint.h>
#include <stddef.h>

#ifdef _cplusplus
  extern "C" {
#endif

#define PHYSICAL_BLOCK_SIZE 4096			//Yeah that is also the size of a page :-)
#define BLOCK_ALIGNMENT BLOCK_SIZE
#define BLCOKS_PER_BYTE 8
#define LEVEL_MULTIPLICATOR 32				// Every level of block is made of 32 previous level elements
#define DOUBLE_LEVEL_MULTIPLICATOR (32*32)
#define TRIPLE_LEVEL_MULTIPLICATOR (32*32*32)



//An alias for uint32_t to refer to the physical memory adresses
typedef uint32_t physical_address;

typedef struct memory_map
{
	uint32_t total_memory;		    // Size of the avaliable memory in kilobytes
	uint32_t used_blocks;		    // The number of blocks currently in use
	uint32_t total_blocks;		    // The maximum number of blocks
	uint32_t total_super_blocks;    // The maximum number of super blocks
	uint32_t total_mega_blocks;		// The maximum number of mega blocks
	
	bitmap_t blocks;

}memory_map_t;


void setup_pmm(multiboot_info_t* multiboot_pointer);

void physical_memory_init_region(physical_address base, size_t size);
void physical_memory_deinit_region(physical_address base, size_t size);

void* physical_memory_alloc_block(void);
void* physical_memory_alloc_blocks(size_t size);

void physical_memory_free_block(void* address);
void physical_memory_free_blocks(void* address, size_t size);


size_t physical_memory_get_memory_size(void);
uint32_t physical_memory_get_block_count(void);
uint32_t physical_memory_get_used_block_count(void);
uint32_t physical_memory_get_free_block_count(void);
uint32_t physical_memory_get_block_size(void);

#ifdef _cplusplus
	}
#endif

#endif // PHYSICAL_MEMORY_H
