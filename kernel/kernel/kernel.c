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
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include <arch/x86/multiboot.h>
#include <arch/x86/timers.h>
#include <arch/x86/acpi.h>
#include <arch/x86/physical_memory.h>
#include <arch/x86/system.h>
#include <devices/keyboard.h>
#include <kernel/tty.h>
#include <kernel/portio.h>

void kernel_early(void)
{
	terminal_setup();
}


void kernel_main(uint32_t eax, multiboot_info_t *multiboot_pointer)
{

	find_tables();
	setup_gdt();
	setup_interrupts();
	install_pit();
	install_rtc();
	setup_pmm(multiboot_pointer);
	install_keyboard();
	enable_print();


	printf("XeonOS - 2016\n");
	printf("CHECKSUM : %x\n", (int)eax);

/*	int c = 0;
	scanf("%d", &c);
*/
	char c[100];
	size_t size = 100;
	getline(c, &size);
	printf("\n%s\n",c);


	while(true) {
		if(kbhit())
			printf("%c", getch());
	}

}