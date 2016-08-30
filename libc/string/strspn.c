/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 13:00:51
* 
* File: strspn.c
* Description: Returns the length of the initial portion of str1
* which consists only of characters that are part of str2.
*/
#include <string.h>

size_t strspn (const char* str1, const char* str2 )
{
	size_t index = 0;

	while(*str1 && strchr(str2, *str1++))
		index++;

	return index;
}