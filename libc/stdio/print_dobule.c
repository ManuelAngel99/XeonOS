/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-22 15:08:55
* 
* File: print_dobule.c
* Description: Implementation of the print double function that prints a floating point number
*/
#include <stdio.h>
#include <math.h>

void print_double(double number)
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
