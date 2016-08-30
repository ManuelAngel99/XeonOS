/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 12:30:21
* 
* File: strchr.c
* Description: Returns a pointer to the first occurrence of character in the string str.
*/
#include <string.h>

char *strchr(const char *str, int character)
{
    while (*str != (char)character)
        if (!*str++)
            return 0;
    
    return (char *)str;
}