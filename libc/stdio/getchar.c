/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 16:44:00
* 
* File: getchar.c
* Description: Implements the C standard getchar function wich returns the first character in the wrote line and prints the input
*/

#include <stdio.h>

int getchar(void)
{
    char buffer[1];
    size_t lenght = 1;
    getline(buffer, &lenght);
    return buffer[0];
}