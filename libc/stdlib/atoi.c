/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-01 18:54:34 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-01 19:24:16
 * 
 * Description: Implements the atoi function that takes a char* and returns an integer with the value contained in the string
 */
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

int atoi(const char* string)
{
    int result = 0;
    while (isspace((unsigned char) *string))
        string++;

    char sign = *string;
    if (*string == '-' || *string == '+')
        string++;

    while (isdigit((unsigned char)*string)) {
        result = result*10 - (*string++ - '0');
    }
    if (sign != '-')
        result = -result;

    return result;
}