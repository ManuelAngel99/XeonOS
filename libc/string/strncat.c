/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 11:46:56
* 
* File: strncat.c
* Description: Implements the strncat function wich appends n chars from the source to the destination
*/
#include <string.h>

char* strncat(char* destination, const char* appendix, size_t lenght)
{
	unsigned int i = strlen(destination);
	while( ( (destination[i] = *appendix++) != '\0' ) && lenght--)
		i++;

	return destination;
}