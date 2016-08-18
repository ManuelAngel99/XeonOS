/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-14 14:19:00
* 
* File: time.h
* Description: Degfines the date time function and some time utilities
*/
#ifndef TIME_H
#define TIME_H

#include <sys/cdefs.h>
#include <stdbool.h>

#define CURRENT_CENTURY 21
#define HOUR_ADJUST 2

#ifdef _cplusplus
	extern "C" {
#endif

typedef struct DateTime
{
	unsigned short second;
	unsigned short minute;
	unsigned short hour;
	unsigned short day;
	unsigned short month;
	unsigned short year;
}DateTime_t;

DateTime_t add_date_times(DateTime_t, DateTime_t);
DateTime_t format_date_time(DateTime_t*);
DateTime_t add_seconds_to_date(DateTime_t*, unsigned int);
void clear_date_time(DateTime_t*);

inline bool is_leap_year(unsigned int year)
{
	return ( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) );
}

#ifdef _cplusplus
}
#endif


#endif // TIME_H
