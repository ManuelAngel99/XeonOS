/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-09-02 10:57:35
* 
* File: vfscanf.c
* Description: Implements the vfscanf function that reads a formated argument list from a file
*/
#include <stdio.h>

int vfscanf(FILE * file_pointer, const char* format, va_list arguments_to_read)
{
    char buffer[BUFSIZ + 1];
    int count = 0;

    if( fgets(buffer, BUFSIZ, file_pointer) == 0 )
        return -1;
    else
        count = vsscanf(buffer, format, arguments_to_read);

    return count;
}
