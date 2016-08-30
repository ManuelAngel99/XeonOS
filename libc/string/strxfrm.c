/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 12:08:11
* 
* File: strxfrm.c
* Description: The strxfrm transforms the string pointed to by source and places the 
* resulting string into the array pointed to by destination.
* The return value is the lenght of the transformed string
* Be careful with overlapping!!
*/
#include <string.h>

size_t strxfrm ( char * __restrict destination, const char * __restrict source, size_t num )
{
	// Be carefull, this implementation only uses the c locale
	size_t lenght_of_source= strlen(source);
    if(num > lenght_of_source)
        strcpy(destination, source);
    
    return lenght_of_source;
}