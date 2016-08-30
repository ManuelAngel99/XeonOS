/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 16:17:17
* 
* File: memmove.c
* Description: Implementation of the c standard memmove function
*
*/

#include <string.h>


/*
* NOTE: Notice that the direction of the copy changes if the src > dst or viceverse
* this is a security measure so even if the two memory segments are one on top of the other we 
* will be able to copy all the bytes
*/

void* memmove(void* destintation_pointer, const void* source_pointer, size_t size)
 {
 	unsigned char* dst = (unsigned char*) destintation_pointer;
 	unsigned char* src = (unsigned char*) source_pointer;

 	if( dst < src)
 	{
 		for(size_t i = 0; i < size; i++)
 			dst[i] = src[i];
 	}
 	else
 	{
 		for(size_t i = size; i != 0; i--)
 			dst[ i - 1] = src[ i - 1];
 	}

 	return destintation_pointer;
 }