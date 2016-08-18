/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-15 12:03:58
* 
* File: add_seconds_to_date.c
* Description: This functions add a number of seconds to a date
*/
#include <time.h>

DateTime_t add_seconds_to_date(DateTime_t* target_date_time, unsigned int seconds)
{
	target_date_time->second += seconds;
	format_date_time(target_date_time);

	return *target_date_time;
}