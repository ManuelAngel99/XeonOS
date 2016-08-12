/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 14:00:08
* 
* File: stdio.h
* Description: Defines the basic input and output functions
*/
#ifndef STDIO_H
#define STDIO_H


#include <sys/cdefs.h>
#include <stddef.h>

#define PRINT_FLOAT_PRECISION 5

#ifdef _cplusplus
	extern "C" {
#endif

int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);

#ifdef _cplusplus
}
#endif

#endif
