/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-14 00:21:20
* 
* File: timers.h
* Description: Defines the timer functions
*/


#ifndef TIMER_H
#define TIMER_H

#ifdef _cplusplus
	extern "C"  {
#endif

#include <arch/x86/interrupts.h>
#include <time.h>

/*
	TIMER FLAGS SETUP: More info at: http://wiki.osdev.org/Programmable_Interval_Timer
	Bits:		Desc:
	0			If set to 1, output will be a 4 digit BCD number, else outout will be binary
	1-3			Operating mode:
					Mode 0 -> Interrupt on terminal count
					Mode 1 -> Harwater re-triggerable one shot
					Mode 2 -> Rate generator 
					Mode 3 -> Square wave generator
	4-5			Access mode:
					Mode 0 -> Latch count value command
					Mode 1 -> Lobyte only
					Mode 2 -> Hibyte only
					Mode 3 -> Lobyte/Hibyte
	6-7			Select channel:
					0 -> Channel 0
					1 -> Channel 1
					2 -> Channel 2
					3 -> Read-back command
	I'll be using the square generator mode accessing both bytes on chanel 0 and i want the output to be a binary
	So the setup would be: 00 11 011 0 -> 0x36 in hexadecimal 
*/
static const uint32_t TIMER_FLAGS = 0x34;
DateTime_t current_date;

void install_pit(void);
void install_rtc(void);


void timer_wait(size_t ticks);
void timer_phase(size_t hz);

DateTime_t get_current_date(void);
void write_cmos_data(uint8_t offset, uint8_t value);
uint8_t read_cmos_byte(uint8_t offset);
int get_cmos_update_in_progress_flag(void);

#ifdef _cplusplus
}
#endif

#endif // TIMER_H

