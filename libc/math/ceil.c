/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-12 23:38:00
* 
* File: ceil.c
* Description: Implements the ceil function
*/
#include <math.h>

double ceil(double value)
{
	int temporal = (int)value;
	return value < temporal ? temporal : temporal + 1;

}