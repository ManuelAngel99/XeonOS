/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-01 19:09:13 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-01 19:55:27
 * 
 * Description: Implements the atof function that takes a string and returns a float
 */

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double atof(const char* string)
 {

     double integer_part = 0, fraction_part = 0;
     int division_for_fraction = 1, sign = 1;
     
     if (!string || !*string)
         return 0; 

    //Skip spaces
    while (isspace((unsigned char) *string))
        string++;

     //Check if the number is negative
     if (*string == '-')
     {
         sign = -1;
         string++;
     }
     else if (*string == '+')
         string++;
    

    while(isdigit(*string))
    {
        integer_part = integer_part * 10 + (*string - '0');
        string++;
    }
    //Decimal part found
    if(*string == '.')
    {
        string++;
        while(isdigit(*string))
        {
            fraction_part = fraction_part*10 + (*string - '0');
            division_for_fraction *= 10;
            string++;
        }

    }

     return (sign * (integer_part + fraction_part/division_for_fraction));
 }