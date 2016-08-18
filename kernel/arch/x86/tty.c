/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 11:44:59
* 
* File: tty.c
* Description: Implements the basic tty functions for the x86 architecture
*/

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/vga.h>
#include <kernel/portio.h>

static volatile size_t cursor_x;
static volatile size_t cursor_y;
uint8_t terminal_color;
uint16_t* terminal_buffer;
size_t tab_size;

void new_line_check(void);
void new_line(void);

void terminal_setup(void)
{
	cursor_x = cursor_y = 0;
	tab_size = 4;
	terminal_color = make_color(WHITE, BLACK);
	terminal_buffer = VIDEO_MEMORY;

	terminal_clear_screen();
}

void terminal_gotoxy(size_t x, size_t y)
{
	if(x < VGA_TERMINAL_WIDTH && y < VGA_TERMINAL_HEIGHT)
	{
		cursor_x = x;
		cursor_y = y;
	}
	update_cursor();
}

int terminal_putentryat(char character, uint8_t color, size_t x, size_t y)
{
	if( cursor_x <= VGA_TERMINAL_WIDTH && cursor_y <= VGA_TERMINAL_HEIGHT)
	{
		const size_t index = (VGA_TERMINAL_WIDTH * y) + x;
		terminal_buffer[index] = make_vgaentry(character, color);
		return 0;
	}

	return -1;
}

void terminal_putchar(char character)
{
	switch(character)
	{
		case '\n':
			new_line();
		break;

		case '\b':
			if(cursor_x > 0)
			{
				cursor_x--;
				terminal_putentryat(' ', terminal_color,cursor_x,cursor_y);
			}
		break;

		case '\r':
			cursor_x = 0;
		break;

		case '\t':
			cursor_x = (cursor_x + tab_size) & ~(tab_size - 1);
		break;

		default:
			terminal_putentryat(character, terminal_color, cursor_x, cursor_y);
			cursor_x++;
		break;
	}

	new_line_check();
	update_cursor();
}

void terminal_write(const char* string, size_t size)
{
	for(size_t i = 0; i < size; i++)
		terminal_putchar(string[i]);
}

void terminal_writestring(const char* string)
{
	terminal_write(string, strlen(string));
}



void terminal_clear_screen(void)
{
	for(size_t y = 0; y < VGA_TERMINAL_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_TERMINAL_WIDTH; x++)
		{
			terminal_buffer[ (VGA_TERMINAL_WIDTH * y) + x] = make_vgaentry(' ', terminal_color);
		}
	}
	cursor_x = cursor_y = 0;
	update_cursor();
}

void terminal_clear_line(size_t line_number)
{
	for (size_t index = line_number * VGA_TERMINAL_WIDTH; index < VGA_TERMINAL_WIDTH * (line_number + 1); index++)
	{
		terminal_buffer[index] = make_vgaentry(' ', terminal_color);
	}
}


void new_line_check(void)
{
	if (cursor_x >= VGA_TERMINAL_WIDTH )
	{
		new_line();
	}
}

void new_line(void)
{
	cursor_x = 0;
	if ( ++cursor_y >= VGA_TERMINAL_HEIGHT )
	{
		scroll_up();
		cursor_y= 24;
	}	
}

void update_cursor(void)
{
	uint16_t position = ( cursor_y * VGA_TERMINAL_WIDTH ) + cursor_x;

	//Write LOW to vga index register
	outport_byte(0x3D4, 14);
	outport_byte(0x3D5, position >> 8 );

	//Write high to vga index register
	outport_byte(0x3D4, 15);
	outport_byte(0x3D5, (uint8_t)position );

}

void scroll_up(void)
{
	for(size_t index = 0; index < VGA_TERMINAL_WIDTH * (VGA_TERMINAL_HEIGHT - 1) ; index++)
		terminal_buffer[index] = terminal_buffer[index + VGA_TERMINAL_WIDTH];

	terminal_clear_line(VGA_TERMINAL_HEIGHT - 1);
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

uint8_t terminal_getcolor(void)
{
	return terminal_color;
}
