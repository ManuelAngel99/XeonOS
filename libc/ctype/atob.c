/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-01 11:06:31 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-01 11:32:33
 * 
 * Description: Implements the atob function that translates an string into an int
 */

#include <ctype.h>
#include <stddef.h>

int atob(size_t* value_store, char* string, int base)
{
    size_t value = 0;
    int digit = 0, sign = 1;
    //Check the base
    if(base == 0)
    {
        if(string[0] == '0')
        {
            switch (string[1])
            {
            case 'x':
            case 'X':
                base = 16;
                break;
            case 't':
            case 'n':
                base = 10;
            case 'o':
                base = 8;
            default:
                base = 10;
                goto skip;
            }

            string += 2;
        }
        else
            return 0;
    }
    
    skip:
    *value_store = value;

    if(*string == '-')
    {
        sign = -1;
        string++;
    }
    else if(*string == '+')
        string++;

    for(; *string; string++)
    {
        if(*string >= '0' && *string <= '9')
            digit = digit_to_int(*string);
        else if(*string >= 'a' && *string <= 'f')
            digit = *string - 'a' + 10;
        else if(*string >= 'A' && *string <= 'F')
            digit = *string - 'A' + 10;
        else
            return 0;
            
        //The specified base is invalid
        if(digit > base)
            return 0;
        value *= base;
        value += digit;
    }

    *value_store = sign*value;

    //Success convering the number
    return 1;
}