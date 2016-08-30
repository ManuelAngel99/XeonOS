/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 12:36:45
* 
* File: strcspn.c
* Description: Scans str1 for the first occurrence of any of the characters that are part
*  of str2, returning the number of characters of str1 read before this first occurrence.
*/
#include <string.h>

size_t strcspn (const char* str, const char* keys)
{
	size_t index = 0;
	while(*str)
	{
		if(strchr(keys, *str))
			return index;				//A key was found, return the index of the last char
		else
			str++, index++;
	}

	return index;
}