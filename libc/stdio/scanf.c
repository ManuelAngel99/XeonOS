/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 15:44:00
* 
* File: scanf.c
* Description: Implements the C standard scanf function
*/

#include <stdio.h>
#include <stdarg.h>

int scanf(const char* restrict format, ...)
{
	va_list list;
	va_start(list, format);
	int result = vfscanf(stdin ,format, list);
	va_end(list);
	return result;
}