/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 12:22:38
* 
* File: memchr.c
* Description: Searches within the first num bytes of the block of memory 
* pointed by ptr for the first occurrence of value (interpreted as 
* an unsigned char), and returns a pointer to it.
*/
#include <string.h>

void* memchr(const void * start, int value, size_t lenght)
{
	unsigned char* pointer = (unsigned char*)start;

	while( lenght-- )
	{
		if( *pointer != (unsigned char)value )
			pointer++;
		else
			return pointer;
	}

    return 0;
}