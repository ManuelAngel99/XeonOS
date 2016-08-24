/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-22 15:07:32
* 
* File: print_int.c
* Description: Implementation of the print int function
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_int(long long number, size_t base)
{
	char* integer_as_string = NULL;
	integer_as_string = itoa( number, integer_as_string, base);
	print(integer_as_string, strlen(integer_as_string));
}