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
#include <stdio.h>

#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <kernel/multiboot.h>
#include <kernel/tty.h>
#include <arch/i386/timer.h>

void kernel_early(void)
{
	terminal_setup();
}

void kernel_main(uint16_t esp, multiboot_info_t *multiboot_pointer)
{
	setup_gdt();
	setup_idt();
	install_timer();
	printf("ESP LOCATION: %x\n", esp );
	printf("UPPER MEMORY: %x\n", (unsigned int)multiboot_pointer->mem_upper);
}