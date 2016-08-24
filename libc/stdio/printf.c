/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 15:44:00
* 
* File: printf.c
* Description: Implements the C standard printf function
*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void print(const char* data, size_t lenght)
{
	for(size_t i = 0; i < lenght; i++)
		putchar( (int) ((const unsigned char* ) data)[i] );
}

int printf(const char* restrict format, ...)
{
	va_list parameters;
	va_start(parameters, format);

	int written = 0;
	char c;
	char* string;

	while(*format != '\0')
	{
		if( *format == '%' )
		{
			format++;
			switch(*format)
			{
				case 'b':
				case 'u':
				case 'x':
				case 'd':
				case 'i':
					print_int(va_arg(parameters,long), (size_t)*format);
					format++;
				break;

				case 'c':
					c = va_arg(parameters, int);
					print( &c, sizeof(c));
					format++;
				break;

				case 'f':
					print_double(va_arg(parameters, double));
					format++;

				case 's':
					string = va_arg(parameters, char*);
					print( string, strlen(string) );
					format++;
				break;

				case '%':
					putchar( (int) '%' );
					format++;
				break;
			}		
		}
		else
		{
			putchar(*format);
			format++;
		}
	}

	va_end(parameters);

	return written;
}