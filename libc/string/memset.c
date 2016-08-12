/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 16:39:17
* 
* File: memset.c
* Description: Implements the c standard library memset function
*/
#include <string.h>

void* memset(void* destination_pointer, int value, size_t size)
{
	unsigned char* buffer = (unsigned char*) destination_pointer;
	for(size_t i = 0; i < size; i++)
		buffer[i] = (unsigned char)value;
	
	return destination_pointer;
}