/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 20:34:08
* 
* File: getch.c
* Description: Implements the getch function wich returns a key from the keyboard buffer
* without printing the input
*/

#include <stdio.h>

#if defined (__is_xeonos_kernel)
#include <devices/keyboard.h>
#endif

int getch(void)
{
	return fgetc(stdin);
}