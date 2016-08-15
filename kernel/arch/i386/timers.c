/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-14 00:28:33
* 
* File: timers.c
* Description: Implements the PIC and the RCT necesary functions
*/

#include <arch/i386/timers.h>
#include <arch/i386/interrupts.h>
#include <kernel/portio.h>
#include <stddef.h>
#include <time.h>


#define BCD_DECODE(unsigned_8bit_number)	((unsigned_8bit_number >> 4) * 10) + (unsigned_8bit_number & 0xF)

size_t timer_ticks = 0;

// Not declared void because they are called with an stack state object that we won't use
void pit_handler();
void rtc_handler();

void pit_handler()
{
	timer_ticks++;
}

void rtc_handler()
{
	static size_t rtc_timer_ticks = 0;
	
	if(rtc_timer_ticks % 1024 == 0)
	{
		add_seconds_to_date(&current_date, 1);
	}

	rtc_timer_ticks++;

	//Important, if we don't read register C rtc interrupts will stop taking
	outport_byte(0x70, 0x0C);	// select register C
	inport_byte(0x71);		// just throw away contents
}


void install_pit(void)
{
	install_irq_handler(0, pit_handler);
}

void timer_phase(size_t hz)
{
    int divisor = 1193180 / hz;       /* Calculate our divisor */
    outport_byte(0x43, 0x36);             /* Set our command byte 0x36 */
    outport_byte(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outport_byte(0x40, divisor >> 8);     /* Set high byte of divisor */
}


void timer_wait(size_t ticks)
{
	size_t elapsed_ticks = ticks + timer_ticks;

	while(timer_ticks < elapsed_ticks);
}

uint8_t read_cmos_byte(uint8_t offset)
{
	outport_byte(cmos_address, offset);
	return inport_byte(cmos_data);
}

void write_cmos_byte(uint8_t offset, uint8_t value)
{
	outport_byte(cmos_address, offset);
	outport_byte(cmos_data, value);
}

void install_rtc(void)
{

	install_irq_handler(8, rtc_handler);

	disable_interrupts();

	char prev = read_cmos_byte(0xB);	// read the current value of register B
	write_cmos_byte(0xB, prev | 0x40 );					// write the previous value ORed with 0x40. This turns on bit 6 of register B

	enable_interrupts();

	current_date = get_current_date();
}

int get_cmos_update_in_progress_flag(void)
{
      outport_byte(cmos_address, 0x0A);
      return (inport_byte(cmos_data) & 0x80);
}

struct DateTime get_current_date(void)
{
	struct DateTime current_date_time;
	uint8_t register_b = read_cmos_byte(0xB);

	uint8_t last_second;
	uint8_t last_minute;
	uint8_t last_hour;
	uint8_t last_day;
	uint8_t last_month;
	uint8_t last_year;

	while(get_cmos_update_in_progress_flag());
	last_second = read_cmos_byte(0x00);
	last_minute = read_cmos_byte(0x02);
	last_hour = read_cmos_byte(0x04);
	last_day = read_cmos_byte(0x07);
	last_month = read_cmos_byte(0x08);
	last_year = read_cmos_byte(0x09);

	/*
	* Read the registers until the same value is obtained twice in a row to prevent inconsistent values due to RTC updates
	*/
	do
	{
		last_second = current_date_time.second;
		last_minute = current_date_time.minute;
		last_hour = current_date_time.hour;
		last_day = current_date_time.day;
		last_month = current_date_time.month;
		last_year = current_date_time.year;

		while(get_cmos_update_in_progress_flag()); 			//Make sure that an update isn't in progress
		current_date_time.second = read_cmos_byte(0x00);
		current_date_time.minute = read_cmos_byte(0x02);
		current_date_time.hour = read_cmos_byte(0x04);
		current_date_time.day = read_cmos_byte(0x07);
		current_date_time.month = read_cmos_byte(0x08);
		current_date_time.year = read_cmos_byte(0x09);

	} while((last_second != current_date_time.second) || (last_minute != current_date_time.minute) || (last_hour != current_date_time.hour) ||
            (last_day != current_date_time.day) || (last_month != current_date_time.month) || (last_year != current_date_time.year) );

	//Some computers give the date in a BCD format so it has to be decoded
	if(!(register_b & 0x04))
	{
		current_date_time.second = BCD_DECODE(current_date_time.second);
		current_date_time.minute = BCD_DECODE(current_date_time.minute);
		current_date_time.hour = BCD_DECODE(current_date_time.year) + HOUR_ADJUST;
		current_date_time.day = BCD_DECODE(current_date_time.day);
		current_date_time.month = BCD_DECODE(current_date_time.month);
		current_date_time.year = BCD_DECODE(current_date_time.year) + ( CURRENT_CENTURY - 1) * 100 ;
	}

	//If the format date is 12 hours change it to 24 hours
	if (!(register_b & 0x02) && (current_date.hour & 0x80))
	{
        current_date.hour = ( (current_date.hour & 0x7F) + 12) % 24;
    }

    //Calculate the full year

	return current_date_time;
}