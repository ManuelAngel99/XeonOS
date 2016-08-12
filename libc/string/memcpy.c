/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 16:44:49
* 
* File: memcpy.c
* Description: Implements the c standart memcpy function
*/

#include <string.h>

void* memcpy(void* restrict destination_pointer, const void* restrict source_pointer , size_t size)
{
	unsigned char* src = (const unsigned char*) source_pointer;
	const unsigned char* dst = (const unsigned char*) destination_pointer;

	for(size_t i = 0; i < size; i++)
		dst[i] = src[i];

	return destination_pointer;
}