/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 21:45:40
* 
* File: print_double.c
* Description: Implements the print double function wich prints a floating point number with a determinated precision
*/
#include <stdio.h>
#include <math.h>

void print_double(double value, size_t precision)
{

	double integer_part = 0;
	double float_part = modf(value,&integer_part);

	float_part = precise_round(float_part, precision);

	while( modf(float_part, NULL) != 0)
	{
		float_part *= 10;
	}

	printf("%d.%d", (int)integer_part, (int)float_part );
}
