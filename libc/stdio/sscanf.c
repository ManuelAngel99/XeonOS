/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-09-02 10:58:27
* 
* File: sscanf.c
* Description: Implementes the sscanf function that reads a formated argument list from a string
*/

#include <stdio.h>
#include <stdarg.h>

int sscanf(const char* buffer, const char* format, ...)
{
    int count;
    va_list parameters_to_read;
    
    //Start the parameter list
    va_start(parameters_to_read, format);

    //Read the parameters from the buffer string
    count = vsscanf(buffer, format, parameters_to_read);
    
    //End the parameter list
    va_end(parameters_to_read);

    return count;
}
