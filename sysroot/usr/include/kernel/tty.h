/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 11:01:21
* 
* File: tty.h
* Description:  Defines the terminal related functions
                As a note, tty stands for TeleTYpe Writer, the name of the first screens used by computers
*/

#ifndef _K_TTY_H
#define _K_TTY_H

#include <stddef.h>
#include <stdint.h>

void terminal_setup(void);

void terminal_putchar(char character);
int terminal_putentryat(char character, uint8_t color, size_t x, size_t y);
void terminal_write(const char* string, size_t size);
void terminal_writestring(const char* string);

void terminal_clear_screen(void);
void terminal_clear_line(size_t line_number);
void scroll_up(size_t number_of_lines);

void terminal_setcolor(uint8_t);
uint8_t terminal_getcolor(void);

#endif // _K_TTY_H
