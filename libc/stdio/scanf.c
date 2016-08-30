/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 15:44:00
* 
* File: scanf.c
* Description: Implements the C standard scanf function
*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int scanf(const char* restrict format, ...)
{
    char input_line[75];                        //The maximum input lenght will be 75 characters
    size_t input_lenght = 75;
	va_list parameters;
	va_start(parameters, format);

    //Get the line that we will parse
    getline(input_line, &input_lenght);

	va_end(parameters);

	return 0;
}