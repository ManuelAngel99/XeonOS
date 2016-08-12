/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-12 23:39:02
* 
* File: pow.c
* Description: Implements the power function
*/
#include <math.h>

double pow(double base, double exponent)
{
	int buffer;
	if( exponent > 0)
	{
		if( ((int)exponent) % 2 == 0 )
		{
			buffer = pow(base, exponent/2);
			return buffer * buffer;
		}
		else
		{
			return base * pow(base, ((int)exponent) -1);
		}
	}
	else if ( exponent < 0)
	{
		return 1.0/pow(base, -exponent);
	}
	//If exponent == 0, return 1
	return 1;
}
