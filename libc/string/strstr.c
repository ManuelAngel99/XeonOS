/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 13:06:18
* 
* File: strstr.c
* Description: This function returns a pointer to the
* first occurence of str 2 in str1 or a null pointer
*/
#include <string.h>

char* strstr(char* str1, const char* str2)
{
	size_t str2_lenght = strlen(str2);
	while(*str1)
	{
		if(!memcmp(str1++, str2, str2_lenght))
			return str1 - 1;
	}

	return NULL;
}