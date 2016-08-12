/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 16:27:07
* 
* File: strlen.c
* Description: Implementation of the strlen C standard function
*/

#include <string.h>

size_t strlen(const char* string) {
	size_t i = 0;

	while(string[i])
		i++;

    return i;
}