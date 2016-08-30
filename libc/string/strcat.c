/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 11:34:25
* 
* File: strcat.c
* Description: The strcat function appends one string to another
*/
#include <string.h>


char* strcat(char* destination, const char* appendix)
{
	unsigned int i = strlen(destination);
	while( (destination[i] = *appendix++) != '\0')
		i++;

	return destination;
}