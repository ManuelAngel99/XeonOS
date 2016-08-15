/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-15 00:42:07
* 
* File: add_date_times.c
* Description: A function that adds two time structuresa and returns the value of the sum
*/
#include <time.h>

struct DateTime add_date_times(struct DateTime first_date, struct DateTime second_date)
{
	//Format the dates before adding them
	format_date_time(&first_date);
	format_date_time(&second_date);

	first_date.second += second_date.second;
	first_date.minute += second_date.minute;
	first_date.hour   += second_date.hour;

	first_date.day	  += second_date.day;
	first_date.month  += second_date.month;
	first_date.year   += second_date.year;

	format_date_time(&first_date);
	return first_date;
}