/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 15:44:00
* 
* File: printf.c
* Description: Implements the C standard printf function
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

static void print(const char* data, size_t lenght)
{
	for(size_t i = 0; i < lenght; i++)
		putchar( (int) ((const unsigned char* ) data)[i] );
}

static void print_int(int number, size_t base)
{
	char* integer_as_string = NULL;
	integer_as_string = itoa( number, integer_as_string, base);
	print(integer_as_string, strlen(integer_as_string));
}

static void print_double(double number)
{
	double integer_part = 0;
	double float_part = modf(number,&integer_part);
	float_part = precise_round(float_part, PRINT_FLOAT_PRECISION);

	while( modf(float_part, NULL) != 0)
		float_part *= 10;

	print_int((int)integer_part, 10);
	putchar( (int)('.'));
	print_int((int)float_part, 10);	
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
				case 'd':
				case 'b':
				case 'u':
				case 'x':
					print_int(va_arg(parameters, int), (size_t)*format);
					format++;
				break;

				case 'c':
					c = va_arg(parameters, int);
					print( &c, sizeof(c));
				break;

				case 'f':
					print_double(va_arg(parameters, double));

				case 's':
					string = va_arg(parameters, char*);
					print( string, strlen(string) );
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