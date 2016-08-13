/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-14 00:21:20
* 
* File: timer.h
* Description: Defines the timer functions
*/


#ifndef TIMER_H
#define TIMER_H

#include <arch/i386/interrupts.h>

void time_handler(struct stack_state stack);
void install_timer();
void timer_wait(size_t ticks);
void timer_phase(size_t hz);
#endif // TIMER_H

