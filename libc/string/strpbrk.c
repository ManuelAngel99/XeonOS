/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 12:46:04
* 
* File: strpbrk.c
* Description: This function returns a pointer to the first occurrence in str1 of any of the
* characters that are part of str2, or a null pointer if there are no matches.

*/
#include <string.h>

char* strpbrk (const char* str, const char* keys)
{
	while(*str)
		if(strchr(keys, *str++))
			return (char*)--str;				//A key was found, return the index of the last char

	return NULL;
}