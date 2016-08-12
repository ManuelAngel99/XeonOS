/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 15:45:02
* 
* File: abort.c
* Description: Implements the abort function that will end the execution of the current program
*/

#include <stdio.h>
#include <stdlib.h>

void abort(void) __attribute__((__noreturn__))
{
	//Need to implement a proper kernel panic
	printf("Kernel Panic: abort\n");
	while(1){}
	__builtin_unreachable();
}