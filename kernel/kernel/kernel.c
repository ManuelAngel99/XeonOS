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

void kernel_main(uint16_t esp, multiboot_info_t *multiboot_pointer)
{
	find_tables();
	setup_gdt();
	setup_interrupts();
	install_pit();
	install_rtc();
	install_keyboard();
	detect_cpu_family();

	printf("XeonOS - 2016\n");
    printf("ESP POINTER LOCATION: %x\n", esp);
    printf("MEMORY UP: %x\n", (int)multiboot_pointer->mem_lower);
	while(true) {
	    char c = (char) keyboard_getch();
		printf("%c", c);
	}

}