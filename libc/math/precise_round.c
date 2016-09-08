/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-12 11:33:48
* 
* File: precise_round.c
* Description: Implements the precise round function wich rounds a floating point number to a certain number of decimal places
*/

#include <math.h>
#include <stddef.h>

long double precise_round(long double value, size_t decimal_paces)
{
	long double fac = pow(10, decimal_paces);
	return roundld(value*fac)/fac;
}