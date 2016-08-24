/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 21:18:08
* 
* File: itoa.c
* Description: Implements the itoa function wich translates an integer into a string
*/
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

char* itoa(long long num, char* str, int base)
{
    size_t i = 0;
    bool is_negative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && ( base == 10 || base == 'd' || base == 'i'))
    {
    	base = 10;
        is_negative = true;
        num = -num;
    }
    else if(base == 'x')
    {
    	base = 16;
    }
    else if(base == 'b')
    {
    	base = 2;
    }
    else
    {
        base = 10;
    }
 
    // Process individual digits
    while (num != 0)
    {
        long long rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (is_negative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}