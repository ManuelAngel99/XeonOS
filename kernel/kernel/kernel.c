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

#include <arch/i386/multiboot.h>
#include <arch/i386/gdt.h>
#include <arch/i386/interrupts.h>
#include <kernel/tty.h>
#include <arch/i386/timers.h>

void kernel_early(void)
{
	terminal_setup();
}

void kernel_main(uint16_t esp, multiboot_info_t *multiboot_pointer)
{
	setup_gdt();
	setup_idt();
	install_pit();
	install_rtc();
	printf("XeonOS -> Checking settings:\n");
	printf("\tESP LOCATION: %x\n", esp );
	printf("\tUPPER MEMORY: %x\n", (unsigned int)multiboot_pointer->mem_upper);
	while(true)
	{
		terminal_gotoxy(62,0);
		printf("%d:%d:%d %d/%d/%d ", current_date.hour, current_date.minute, current_date.second,
			 	current_date.day, current_date.month, current_date.year);
	}
}