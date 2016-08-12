/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-12 11:36:55
* 
* File: round.c
* Description: Implements the integer round function
*/
#include <math.h>

int round(double value)
{
	return (int)(value < 0 ? (value - 0.5) : (value + 0.5));
}