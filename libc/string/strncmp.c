/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 11:58:31
* 
* File: strncmp.c
* Description: Implements the strncmp function that compares n characters
* form two strings and returns 0 if they are the same
*/
#include <string.h>

int strncmp(const char* strn1, const char* strn2, size_t number)
{
    while(number--)
        if(*strn1++!=*strn2++)
            return *(unsigned char*)(strn1 - 1) - *(unsigned char*)(strn2 - 1);
    return 0;
}