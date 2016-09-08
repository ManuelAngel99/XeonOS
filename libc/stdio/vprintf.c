/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-09-02 11:56:15
* 
* File: vprintf.c
* Description: The vfprintf function prints a formatted argument list to stdout
*/
#include <stdio.h>
#include <stdarg.h>

int vprintf (const char *format, va_list arguments)
{
	return vfprintf (stdout, format, arguments);
}