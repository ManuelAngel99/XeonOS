/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-08 11:53:36 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-08 12:51:32
 * 
 * Description: This functions takes a string wich contains a number in a certain base and translates it to a long
 */

#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

long strtol(const char* number_string, char** end_pointer, int base)
{
    unsigned long acc, cutoff;
    int c, any, cutlim;
    const char* s = number_string;
    bool is_negative = false;

    //Skip empty spaces
    do
    {
        c = *s++;
    }while(isspace(c));
    
    //Check for negative sign
    if( c == '-' )
    {
        c = *s++;
        is_negative = true;
    }
    //Advamce  a char
    else if( c == '+' )
        c = *s++;
    
    //If no base is specified chack for 0x -> (base = 16) and 0 -> octal
    if( c == '0' && (base == 0 || base == 16) && (*s == 'x' || *s == 'X') )
    {
        c = s[1];
        s += 2;
        base = 16;
    }
    if(base == 0)
        base = c == '0' ? 8 : 10;


    /*
     * The cutoff value is the largest legal value divided by the base
     * any is set if any digit is found or is -1 if a overflow occur
    */
    cutoff = is_negative? -(unsigned long)INT32_MIN: INT32_MAX;
    cutlim = cutoff % (unsigned long)base;
    cutoff /= base;

    for(acc = 0, any = 0;; c = *s++)
    {
        if(isdigit(c))
            c -= '0';
        else if(isalpha(c))
            c -= isupper(c) ? 'A' - 10 : 'a' - 10;
        else
            break;
        
        if( c >= base)
            break;
        if(any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else
        {
            any = 1;
            acc *= base;
            acc += c;
        }
    }
    if( any < 0)
        acc = is_negative ? INT32_MIN : INT32_MAX;
    else if(is_negative)
        acc = -acc;
    
    if(end_pointer != 0)
        *end_pointer = (char*)(any ? s - 1 : number_string);

    return acc;
}