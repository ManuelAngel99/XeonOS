/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-12 23:37:27
* 
* File: floor.c
* Description: Implements the floor function
*/
#include <math.h>

double floor(double value)
{
	int temporal = (int)value;
	return value < temporal ? temporal -1 : temporal;
}