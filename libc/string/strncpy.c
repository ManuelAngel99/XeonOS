/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 11:29:34
* 
* File: strncpy.c
* Description: Implementation of the strncpy function that copies n characters from a string to another
*/
#include <string.h>

char* strncpy(char* destination, const char* source, size_t number)
{
	if(number == 0)
		return destination;

	while( (*destination++ = *source++) != '\0' && number--)
		;

	return destination;
}