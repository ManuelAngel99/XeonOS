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

#include <kernel/tty.h>

void kernel_early(void)
{
	terminal_setup();
}

void kernel_main(void)
{
	putchar('c');
	printf("ITS ALIVE\nI MEAN, ITS ALIVE!%d",12);
}