/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-09-02 11:18:55
* 
* File: fprintf.c
* Description: Implements the fprintf function that sends a bunch of formatted data to a stream
*/
#include <stdio.h>
#include <stdarg.h>

int fprintf(FILE *file_stream, const char* restrict format, ...)
{
	int lenght;
	va_list parameters;
	va_start(parameters, format);

	lenght = vfprintf(file_stream, format, parameters);

	va_end(parameters);

	return lenght;
}