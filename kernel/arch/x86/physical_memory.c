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

static uint32_t get_grub_total_kbytes_of_memory(multiboot_info_t* multiboot_pointer, uint32_t mem_upper);
static void setup_physical_memory_map(uint32_t total_kbytes, physical_address_t* bitmap_start);

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

static void setup_physical_memory_map(uint32_t total_kbytes, physical_address_t* bitmap_start)
{
	//Set the memory size
	physical_memory.total_memory = total_kbytes;
	physical_memory.total_blocks = total_kbytes/4;

	//Init the bitmap
	bitmap_initialize(&physical_memory.blocks, physical_memory.total_blocks, bitmap_start);

	//By default all memory is in use
	bitmap_set_range(&physical_memory.blocks, 0, physical_memory.total_blocks);
	physical_memory.used_blocks = physical_memory.total_blocks;
}


void setup_pmm(multiboot_info_t* multiboot_pointer)
{
	//End of kernel symbol is defined in the linker.ld
	extern uint32_t end_of_kernel;
	physical_address_t* bitmap_start = (physical_address_t*) &end_of_kernel;

	uint32_t total_kb = get_grub_total_kbytes_of_memory(multiboot_pointer, multiboot_pointer->mem_upper);
	multiboot_memory_map_t* grub_memory_map = (multiboot_memory_map_t*)multiboot_pointer->mmap_addr;

	setup_physical_memory_map(total_kb, bitmap_start);

	while(grub_memory_map < (multiboot_memory_map_t*)(multiboot_pointer->mmap_addr + multiboot_pointer->mmap_length))
	{

		#ifdef NDEBUG
			printf("Base adresses %x ", (uint32_t)(grub_memory_map->addr)/1024);
			printf(",length %x ", (uint32_t)(grub_memory_map->len)/1024);
			printf(",memory type %x\n", grub_memory_map->type);
		#endif // NDEBUG

		if(grub_memory_map->type == 1 && (grub_memory_map->addr/1024) > multiboot_pointer->mem_lower) //Free the avaliable regions of the memory except the low adresses (BIOS)
			physical_memory_deinit_region((physical_address_t)grub_memory_map->addr, (size_t)(grub_memory_map->len));

	    grub_memory_map = (multiboot_memory_map_t*) + ( (unsigned int)grub_memory_map + grub_memory_map->size + 4 );
	}

	//Alloc the kernel region and the bitmap region
	physical_memory_init_region(0x0, (physical_address_t)&end_of_kernel);
	physical_memory_init_region((physical_address_t)bitmap_start,
								(physical_address_t)(sizeof(memory_map_t) + physical_memory.total_blocks) * 8);

	#ifdef NDEBUG
		printf("TOTAL KB OF MEM: %d \n", total_kb);
		printf("BLOCKS TOTAL/USED: %d/%d\n",physical_memory.total_blocks, physical_memory.used_blocks);
	#endif //NDEBUG
}


void physical_memory_init_region(physical_address_t base, size_t length)
{
	bitmap_set_range( &physical_memory.blocks, base /PHYSICAL_BLOCK_SIZE, length/PHYSICAL_BLOCK_SIZE);
	physical_memory.used_blocks += length/PHYSICAL_BLOCK_SIZE;
}

void physical_memory_deinit_region(physical_address_t base, size_t length)
{
	bitmap_clear_range( &physical_memory.blocks, base /PHYSICAL_BLOCK_SIZE, length/PHYSICAL_BLOCK_SIZE);
	physical_memory.used_blocks -= length/PHYSICAL_BLOCK_SIZE;
}

void* physical_memory_alloc(size_t number_of_blocks)
{
	size_t starting_block = 0;
	if(bitmap_allocate_range(&physical_memory.blocks, number_of_blocks, 1024, 0, 0, &starting_block))
	{
		physical_memory.used_blocks += number_of_blocks;
		return (void*)(starting_block * PHYSICAL_BLOCK_SIZE);
	}
	return NULL;
}

void physical_memory_free(void* address, size_t number_of_blocks)
{
	physical_memory.used_blocks -= number_of_blocks;
	bitmap_clear_range(&physical_memory.blocks, (uint32_t)address / PHYSICAL_BLOCK_SIZE, number_of_blocks);
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