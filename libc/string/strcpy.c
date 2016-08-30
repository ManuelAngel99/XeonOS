/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 11:26:57
* 
* File: strcpy.c
* Description: Implementation of the strcpy funcion that copies a string into another string
*/
#include <string.h>

char* strcpy(char* destination, const char* source)
{
	while( (*destination++ = *source++) != '\0')
		;

	return destination;
}