/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-18 12:51:00
* 
* File: paging.h
* Description: Header that describes the definitions of the paging code
*/
#ifndef KERNEL_PAGING_H
#define KERNEL_PAGING_H


#include <arch/x86/physical_memory.h>

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define PAGES_PER_TABLE 1024
#define TABLES_PER_DIR 1024

#define PAGE_SIZE 4096

#define PAGE_DIRECTORY_INDEX(x) (((x) >> 22) & 0x3ff)
#define PAGE_TABLE_INDEX(x) (((x) >> 12) & 0x3ff)
#define PAGE_GET_PHYSICAL_ADDRESS(x) (*x & ~0xfff)

#define PAGE_TABLE_ADDRESS_SIZE	0x400000

#define DIRECTORY_TABLE_ADRESS_SIZE 0x100000000

#ifdef _cplusplus
  extern "C" {
#endif
  	
typedef uint32_t virtual_address;

/*
*	Page directory entries:
*   Bits:		Description:
*	0			(1) Page is present, 	(0) Page is not present
*	1			(1) Page is writeable 	(0) Page can only be read
*	2			(1) User mode page 		(0) Kernel mode page
*	3			(1) Write trhough enable(0) Write through cache disabled
*	4			(1) Cache disabled		(0) Cache enablled
*	5			(1) Page accessed		(0) The page hasn't been accessed yet
*	6			(1) Page written		(10) Page hasn't been writen to
*	7-8			Reserved by the cpu
*	9-11		Available for kernel use
*	12-31		Page frame buffer
*/


enum page_table_entry_flags
{
	pte_present       = 1,        // Bit 0
	pte_writeable     = 4,        // Bit 1
	pte_user_mode     = 4,        // Bit 2
	pte_writethough   = 8,        // Bit 3
	pte_not_cacheable = 0x10,     // Bit 4
	pte_accessed      = 0x20,     // Bit 5
	pte_dirty         = 0x40,     // Bit 6
	pte_pat           = 0x80,     // Bit 7
	pte_cpu_global    = 0x100,    // Bit 8
	pte_lv4_global    = 0x200,    // Bit 9
	pte_frame_number  = 0x7FFFF000 // Bits 12-31
} page_table_entry_flags;

// Set an alias for uint32_t to refer to a page table entry
typedef uint32_t page_table_entry;

extern void add_attribute_to_pte(page_table_entry* entry, uint32_t attribute);   // Set an attributerto a page entry
extern void del_attribute_from_pte(page_table_entry* entry, uint32_t attribute); // Remove an attributerto from page entry
extern void set_pte_frame(page_table_entry* entry, physical_address);            // Sets gtame to a page entry
extern bool pte_is_present(page_table_entry entry);                              // Check if a page is present
extern bool pte_is_writable(page_table_entry entry);                             // Check if a page is writteable
extern physical_address page_table_entry_pfn(page_table_entry entry);            // Get the page frame number from an entry


/*
*	Page directory:
*   Bits:		Description:
*	0			(1) Page is present, 	(0) Page is not present
*	1			(1) Page is writeable 	(0) Page can only be read
*	2			(1) User mode page 		(0) Kernel mode page
*	3			(1) Write trhough enable(0) Write through cache disabled
*	4			(1) Cache disabled		(0) Cache enablled
*	5			(1) Page accessed		(0) The page hasn't been accessed yet
*	6			(1) Page written		(10)Page hasn't been writen to
*	7			(1) Page size = 4 MiB	(0) Page size = 4KiB
*	9-11		Available for kernel use
*	12-31		Page frame address				
*/

enum page_directory_entry_flags
{
	pde_present        = 1,        // Bit 0
	pde_writeable      = 4,        // Bit 1
	pde_user_mode      = 4,        // Bit 2
	pde_writethough    = 8,        // Bit 3
	pde_cache_disabled = 0x10,     // Bit 4
	pde_accessed       = 0x20,     // Bit 5
	pde_dirty          = 0x40,     // Bit 6
	pde_size_4mb       = 0x80,     // Bit 7
	pde_cpu_global     = 0x100,    // Bit 8
	pde_lv4_global     = 0x200,    // Bit 9
	pde_frame_number   = 0x7FFFF000 // Bits 12-31
}page_directory_entry_flags;

// Set an alias for uint32_t to refer to a page table entry
typedef uint32_t page_directory_entry;

extern void add_attribute_to_pde(page_directory_entry* entry, uint32_t attribute);   // Set an attributerto a page directory entry
extern void del_attribute_from_pde(page_directory_entry* entry, uint32_t attribute); // Remove an attributerto from page directory entry
extern void set_pde_frame(page_directory_entry* entry, physical_address);            // Sets frame to a page entry
extern bool pde_is_present(page_directory_entry entry);                              // Check if a page is present
extern bool pde_is_user(page_directory_entry entry);                                 // Check if a page is in user mode
extern bool pde_is_4mb(page_directory_entry entry);                                  // Check if a page is 4mb in size
extern bool pde_is_writable(page_directory_entry entry);                      	     // Check if a page is writteable
extern physical_address page_directory_entry_pfn(page_directory_entry entry);        // Get the page frame number from an entry
extern void pde_enable_global(page_directory_entry entry);                           // Make a page globaly avaliable


typedef struct PageTable
{
	page_table_entry page[1024];
}PageTable_t;

typedef struct PageDirectoryTable
{
	page_directory_entry page_directory[1024];
}PageDirectoryTable_t;



#ifdef _cplusplus
	}
#endif




#endif // KERNEL_MEMORY_H
