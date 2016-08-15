/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-15 11:45:15
* 
* File: clear_date_time.c
* Description: A function that clears a date time to 0s
*/
#include <time.h>

void clear_date_time(struct DateTime* date_time_to_clear)
{
	date_time_to_clear->second = 0;
	date_time_to_clear->minute = 0;
	date_time_to_clear->hour = 0;
	date_time_to_clear->day = 0;
	date_time_to_clear->month = 0;
	date_time_to_clear->year = 0;
}
