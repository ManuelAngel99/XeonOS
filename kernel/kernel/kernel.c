/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 11:09:50
* 
* File: kernel.c
* Description: Constains the kernel_main function
*/

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <arch/x86/multiboot.h>
#include <arch/x86/timers.h>
#include <arch/x86/acpi.h>
#include <arch/x86/system.h>
#include <devices/keyboard.h>
#include <kernel/tty.h>
#include <kernel/portio.h>

void kernel_early(void)
{
	terminal_setup();
}

void print_memory_map(multiboot_info_t* multiboot_pointer)
{
	printf("\n\t\tMEMORY MAP:\n");
	multiboot_memory_map_t* grub_memory_map = (multiboot_memory_map_t*)multiboot_pointer->mmap_addr;
	while(grub_memory_map < (multiboot_memory_map_t*)(multiboot_pointer->mmap_addr + multiboot_pointer->mmap_length))
	{
		printf("Base adresses %x ", (uint32_t)(grub_memory_map->addr)/1024);
		printf(",length %x ", (uint32_t)(grub_memory_map->len)/1024);
		printf(",memory type %x\n", grub_memory_map->type);

	    grub_memory_map = (multiboot_memory_map_t*) + ( (unsigned int)grub_memory_map + grub_memory_map->size + 4 );
	}
}

void kernel_main(uint32_t eax, multiboot_info_t *multiboot_pointer)
{

	find_tables();
	setup_gdt();
	setup_interrupts();
	install_pit();
	install_rtc();
	install_keyboard();
	detect_cpu_family();


	printf("XeonOS - 2016\n");
    printf("MULTBOOT MAGIC: %x\n", (int)eax);
    printf("MULTBOOT FLAGS: %x\n", (int)multiboot_pointer->flags);
    printf("MEMORY UP:\t %x\n", (int)multiboot_pointer->mem_upper);
    printf("MEMORY LOW:\t %x\n", (int)multiboot_pointer->mem_lower);

    print_memory_map(multiboot_pointer);

    char c;

	while(true) {
	    c = (char) keyboard_getch();
		printf("%c", c);
	}

}