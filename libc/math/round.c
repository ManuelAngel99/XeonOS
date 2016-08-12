/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-12 23:35:40
* 
* File: round.c
* Description: Implements the round function
*/
#include <math.h>

double round(double value)
{
	return (int)(value < 0 ? (value - 0.5) : (value + 0.5));
}