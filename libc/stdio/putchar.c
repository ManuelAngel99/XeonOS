/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 20:00:42
* 
* File: putchar.c
* Description: Implements the function putchar wich outputs a single character to the screen
*/
#include <stdio.h>

#if defined (__is_xeonos_kernel)
#include <kernel/tty.h>
#endif


int putchar(int integer_character)
{
#if defined(__is_xeonos_kernel)
	char character = (char)integer_character;
	terminal_putchar(character);
#else
	//TODO: IMPLEMENT A SYSTEM CALL
#endif
	return integer_character;
}