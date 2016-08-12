/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-12 11:29:36
* 
* File: ceil.c
* Description:
*//*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-12 11:29:36
* 
* File: ceil.c
* Description: Implements the ceil function wich return the closest greater integer of a number 
*/

#include <math.h>

int ceil(double value)
{
	int temporal = (int)value;
	return value < temporal ? temporal : temporal + 1;

}