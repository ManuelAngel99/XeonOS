/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-09-02 11:52:41
* 
* File: vfprintf.c
* Description: The vfprintf function prints a formatted argument list to a file stream
*/
#include <stdio.h>
#include <stdarg.h>

int vfprintf (FILE * file_stream, const char*  __restrict format, va_list arguments)
{
	int  lenght;
	char buffer[1024];

	lenght = vsprintf (buffer, format, arguments);
	fputs (buffer, file_stream);

	return lenght;
}
