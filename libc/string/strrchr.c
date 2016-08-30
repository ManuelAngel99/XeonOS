/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 12:54:30
* 
* File: strrchr.c
* Description: This function locates the las occurence of character casted to a char in the str provided
*/
#include <string.h>


char * strrchr (char* str, int character)
{
	char* return_value = NULL;

	do
	{
		if( *str == (char)character )
			return_value = str;
	} while(*str++);

	return return_value;
}