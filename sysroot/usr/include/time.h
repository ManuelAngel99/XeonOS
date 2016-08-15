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
#define HOUR_ADJUST - 4

#ifdef _cplusplus
	extern "C" {
#endif

struct DateTime
{
	unsigned short second;
	unsigned short minute;
	unsigned short hour;
	unsigned short day;
	unsigned short month;
	unsigned short year;
}DateTime_t;

struct DateTime add_date_times(struct DateTime, struct DateTime);
struct DateTime format_date_time(struct DateTime*);
void clear_date_time(struct DateTime*);
struct DateTime add_seconds_to_date(struct DateTime*, unsigned int);

inline bool is_leap_year(unsigned int year)
{
	return ( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) );
}

#ifdef _cplusplus
}
#endif


#endif // TIME_H
