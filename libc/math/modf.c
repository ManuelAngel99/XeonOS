/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-12 11:31:13
* 
* File: modf.c
* Description: Implements the modf function wich returns returns the fraction component (part after the decimal), and sets integer to the integer component.
*/

#include <math.h>	

double modf(double value, double* intpart)
{
	double decimal_part = 0.0;
	if( value >= 0)
	{
		decimal_part = value - (double)floor(value);
		*intpart = value - decimal_part;
	}
	else 
	{
		decimal_part = -(value - (double)ceil(value));
		*intpart = value + decimal_part;
	}
	return decimal_part;
}
