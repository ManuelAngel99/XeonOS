/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-12 11:27:27
* 
* File: floor.c
* Description: Implements the floor function wich return the less greatest integer below a number
*/

#include <math.h>

int floor(double value)
{
	int temporal = (int)value;
	return value < temporal ? temporal -1 : temporal;
}