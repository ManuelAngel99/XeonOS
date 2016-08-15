/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook->com
* Created: 2016-08-15 11:03:08
* 
* File: format_date_time.c
* Description: Implements the format_date_time function that re-formats a date if seconds > 60, minutes > 60 etc etc
*/

#include <time.h>

struct DateTime format_date_time(struct DateTime* date_to_fix)
{
	if(date_to_fix->second >= 60)
	{
		date_to_fix->second = 0;
		date_to_fix->minute++;
	}
	if(date_to_fix->minute >= 60)
	{
		date_to_fix->minute = 0;
		date_to_fix->hour++;
	}
	if(date_to_fix->hour >= 24)
	{
		date_to_fix->hour = 0;
		date_to_fix->day++;
	}
	if(date_to_fix->day >= 28)
	{
		unsigned int number_of_days;
		
		if(date_to_fix->month == 4 || date_to_fix->month == 6 || date_to_fix->month == 9 || date_to_fix->month == 11)
			number_of_days = 30;
		else if(date_to_fix->month == 2)
			if(is_leap_year(date_to_fix->year))
				number_of_days = 29;
			else
				number_of_days = 28;
		else
			number_of_days = 31;

		if(date_to_fix->day > number_of_days)
			date_to_fix->day = 1;
			date_to_fix->month++;
	}
	if(date_to_fix->month > 12)
	{
		date_to_fix->month = 1;
		date_to_fix->year++;
	}


	return *date_to_fix;
}