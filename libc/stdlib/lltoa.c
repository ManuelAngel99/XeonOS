/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-08 10:53:38 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-08 11:06:15
 * 
 * Description: Implements the lltoa function that translates a long long to a string
*/

#include <stdlib.h>
#include <stdbool.h>

char* lltoa(long long value, char* result, int base)
{
	// check that the base if valid
	if ((base < 2 || base > 36) && base != -10) { *result = '\0'; return result; }

	char* pointer = result, *aux_pointer = result, tmp_char;
	long long tmp_value;
	bool negative = false;
	
	if(base == -10)
	{
		base = 10;
		if( value & (1LL << 63))
		{
			value = (~value) + 1;
			negative = true;
		}
	}

	do {
		tmp_value = value;
		value /= base;
		*pointer++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (negative) *pointer++ = '-';
	*pointer-- = '\0';
	
	//Reverse the string
	while(aux_pointer < pointer) {
		tmp_char = *pointer;
		*pointer--= *aux_pointer;
		*aux_pointer++ = tmp_char;
	}
	return result;
}