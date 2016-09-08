/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-09-02 10:59:32
* 
* File: fscanf.c
* Description: Implements the fscanf function that reads an argunent list from a formatted file
*/
#include <stdio.h>
#include <stdarg.h>

int fscanf(FILE* file_pointer, const char *format, ...)
{
    int count;
    va_list parameters_to_read;
    
    //Start the parameter list
    va_start(parameters_to_read, format);

    //Read the parameters from a file
    count = vfscanf(file_pointer, format, parameters_to_read);

    //End the parameters list
    va_end(parameters_to_read);

    return count;
}