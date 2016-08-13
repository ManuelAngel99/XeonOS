/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-14 00:28:33
* 
* File: timer.c
* Description:
*/
#include <arch/i386/timer.h>
#include <kernel/portio.h>
#include <stddef.h>
#include <stdio.h>

size_t timer_ticks = 0;

void time_handler(struct stack_state stack)
{
	timer_ticks++;
	stack.error_code++;
	if(timer_ticks % 100 == 0)
	{
		printf("A second has passed\n");
	}
}

void timer_phase(size_t hz)
{
    unsigned int divisor = 1193180 / hz;       /* Calculate our divisor */
    outport_byte(0x43, 0x36);             /* Set our command byte 0x36 */
    outport_byte(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outport_byte(0x40, divisor >> 8);     /* Set high byte of divisor */
}

void install_timer()
{
	timer_phase(100);
	install_irq_handler(0, time_handler);
}
void timer_wait(size_t ticks)
{
	size_t elapsed_ticks = ticks + timer_ticks;

	while(timer_ticks < elapsed_ticks);
}