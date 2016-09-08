/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 15:44:00
* 
* File: printf.c
* Description: Implements the C standard printf function
*/

#include <stdio.h>
#include <stdarg.h>


int printf(const char* __restrict format, ...)
{
	int lenght;
	va_list parameters;
	va_start(parameters, format);

	lenght = vfprintf(stdout, format, parameters);

	va_end(parameters);

	return lenght;
}