/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 15:44:00
* 
* File: printf.c
* Description: Implements the C standard printf function
*/

#include <stdbool.h>
#include <stdlib>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void print(const char* data, size_t lenght)
{
	for(size_t i = 0; i < lenght; i++)
		putchar( (int) ((const unsigned char* ) data)[i] );
}

static void print_int(int number, size_t base)
{
	char* integer_as_string = itoa( number, integer_as_string, base);
	print(integer_as_string, strlen(integer_as_string));
}

int printf(const char* restrict format, ...)
{
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while(*format != '\0')
	{
		if( *format == '%' )
		{
			*format++;
			switch(*format)
			{
				case 'd':
				case 'b':
				case 'u':
				case 'x':
					print_int(va_arg(parameters, int), (size_t)*format);
				break;

				case 'c':
					char character = (char) va_arg(parameters, int);
					print( &character, sizeof(character));
				break;

				case 'f':
					double integer_part = 0;
					double float_part = modf(value,&integer_part);
					float_part = precise_round(float_part, precision);
					
					while( modf(float_part, NULL) != 0)
						float_part *= 10;

					printf("%d.%d", (int)integer_part, (int)float_part );
				break;

				case 's':
					const char* string = va_arg(parameters, const char*);
					print( string, strlen(string) );
				break;

				case '%':
					putchar( (int) '%' );
					*format++;
				break;
			}		
		}
	}

	va_end(parameters);

	return written;
}