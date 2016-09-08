/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-08 11:06:30 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-08 11:35:31
 * 
 * Description: Implements the ldtoa function that translates a long double into a string
 */

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <string.h>

char* ldtoa(long double number, char* buffer, int precission, bool use_exponent_notation)
{
	 char  reversed_int_part[311];
	 int i, count = 0, exponent = 0;
	 long double number_int_part, number_fractional_part;
	 bool is_negative = false, first_digit_found = false;
	 
	//Check for NaN and infinities
	if(number != number)
		return (buffer = "nan");
	else if(number == LDBL_MAX)
		return (buffer = "inf");
	else if(number == LDBL_MIN)
		return (buffer = "-inf");
	
	//Check if the number is negative
	if(number < 0)
	{
		is_negative = true;
		number = -number;
	}
	
	//Separate integer/fractional parts
	number_fractional_part = modld(number ,&number_int_part);
	number_fractional_part = precise_round(number_fractional_part, precission);
	
	while (number_int_part > 0)
	{
		reversed_int_part[count++] = '0' + (int)fmod(number_int_part,10);
		number_int_part = floorld(number_int_part/10);
		exponent++;
		first_digit_found = true;
	}
	
	
	//Append a 0 to the int part
	if(number_int_part == 0)
	{
		exponent = -1;
		if(!use_exponent_notation)
			reversed_int_part[count++] = '0';
	}
	
	//Ad the minus sign
	if(is_negative)
		reversed_int_part[count++] = '-';
		

	for (i=0; i<count; i++) //Reverse the integer part, if any
		buffer[i] = reversed_int_part[count-i-1];

	// Add a decimal point
	if(!use_exponent_notation)
		buffer[count++] = '.';
	
	//Parse the decimal part
	while (number_fractional_part > 0 && precission-- >= 0)
	{
		number_fractional_part*=10;
		number_fractional_part = modld(number_fractional_part,&number_int_part);
		
		if(use_exponent_notation && number_int_part == 0 && !first_digit_found)
			exponent--;
		else
		{
			first_digit_found = true;
			buffer[count++] = '0' + (int)number_int_part;
		}
	}
	
	//Add the missing zeros
	if( !number_fractional_part )
	{
		buffer[count++] = '0';
		if(!number_int_part && use_exponent_notation)
			buffer[count++] = '0';
	}
	
	if(use_exponent_notation)
	{
		insert_char(buffer, count++ + 1 , '.', 1 + is_negative);
		buffer[count++] = 'e';
		lltoa(exponent, buffer + count , -10);
	}
	else
		buffer[count] = 0; //String terminator
	return buffer;
}
