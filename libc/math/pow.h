/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-12 11:35:09
* 
* File: pow.h
* Description: Implements the pow function
*/
#include <math.h>

double pow(double base, int exponent)
{
	int buffer;
	if( exponent > 0)
	{
		if(exponent % 2 == 0 )
		{
			buffer = pow(base, exponent/2);
			return buffer * buffer;
		}
		else
		{
			return base * pow(base, exponent -1);
		}
	}
	else if ( exponent < 0)
	{
		return 1.0/pow(base, -exponent);
	}
	else
	{
		return 1;
	}
}