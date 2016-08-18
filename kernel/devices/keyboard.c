/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-17 10:00:53
* 
* File: keyboard.c
* Description: Implementations of the keyboard functions
*/

#include <devices/keyboard.h>
#include <arch/x86/interrupts.h>
#include <arch/x86/system.h>
#include <arch/x86/timers.h>
#include <kernel/portio.h>

#include <stdbool.h>
#include <stdio.h>

static bool shift=false, alt=false, control=false, caps_lock = false, key_pressed;
static unsigned char keyboard_buffer[129];
static volatile unsigned int buffer_end = 0;


unsigned short keyboard_unshifted[] =
{
    KEY_UNKNOWN, ASCII_ESC, '1', '2',   /* 0x00 - 0x03 */
    '3', '4', '5', '6',                 /* 0x04 - 0x07 */
    '7', '8', '9', '0',                 /* 0x08 - 0x0B */
    '\'', '¡', ASCII_BS, '\t',           /* 0x0C - 0x0F */
    'q', 'w', 'e', 'r',                 /* 0x10 - 0x13 */
    't', 'y', 'u', 'i',                 /* 0x14 - 0x17 */
    'o', 'p', '`', '+',                 /* 0x18 - 0x1B */
    '\n', KEY_LCTRL, 'a', 's',          /* 0x1C - 0x1F */
    'd', 'f', 'g', 'h',                 /* 0x20 - 0x23 */
    'j', 'k', 'l', 'ñ',                 /* 0x24 - 0x27 */
    '\'', KEY_UNKNOWN, KEY_LSHIFT, 'ç',        /* 0x28 - 0x2B */
    'z', 'x', 'c', 'v',                 /* 0x2C - 0x2F */
    'b', 'n', 'm', ',',                 /* 0x30 - 0x33 */
    '.', '-', KEY_RSHIFT, KEY_PRINTSCRN, /* 0x34 - 0x37 */
    KEY_LALT, ' ', KEY_CAPSLOCK, KEY_F1, /* 0x38 - 0x3B */
    KEY_F2, KEY_F3, KEY_F4, KEY_F5,     /* 0x3C - 0x3F */
    KEY_F6, KEY_F7, KEY_F8, KEY_F9,     /* 0x40 - 0x43 */
    KEY_F10, KEY_NUMLOCK, KEY_SCRLOCK, KEY_KPHOME,  /* 0x44 - 0x47 */
    KEY_KPUP, KEY_KPPGUP, KEY_KPMINUS, KEY_KPLEFT,  /* 0x48 - 0x4B */
    KEY_KPCENTER, KEY_KPRIGHT, KEY_KPPLUS, KEY_KPEND,  /* 0x4C - 0x4F */
    KEY_KPDOWN, KEY_KPPGDN, KEY_KPINSERT, KEY_KPDEL,  /* 0x50 - 0x53 */
    KEY_SYSREQ, KEY_UNKNOWN, '<', KEY_UNKNOWN,  /* 0x54 - 0x57 */
};

unsigned short keyboard_shifted[]={
    KEY_UNKNOWN, ASCII_ESC, '!', '\"',   /* 0x00 - 0x03 */
    '·', '$', '%', '&',                 /* 0x04 - 0x07 */
    '/', '(', ')', '=',                 /* 0x08 - 0x0B */
    '?', '¿', ASCII_BS, '\t',           /* 0x0C - 0x0F */
    'Q', 'W', 'E', 'R',                 /* 0x10 - 0x13 */
    'T', 'Y', 'U', 'I',                 /* 0x14 - 0x17 */
    'O', 'P', '{', '}',                 /* 0x18 - 0x1B */
    '\n', KEY_LCTRL, 'A', 'S',          /* 0x1C - 0x1F */
    'D', 'F', 'G', 'H',                 /* 0x20 - 0x23 */
    'J', 'K', 'L', 'Ñ',                 /* 0x24 - 0x27 */
    '¨', KEY_UNKNOWN, KEY_LSHIFT, 'Ç',          /* 0x28 - 0x2B */
    'Z', 'X', 'C', 'V',                 /* 0x2C - 0x2F */
    'B', 'N', 'M', ';',                 /* 0x30 - 0x33 */
    ':', '_', KEY_RSHIFT, KEY_PRINTSCRN, /* 0x34 - 0x37 */
    KEY_LALT, ' ', KEY_CAPSLOCK, KEY_F1, /* 0x38 - 0x3B */
    KEY_F2, KEY_F3, KEY_F4, KEY_F5,     /* 0x3C - 0x3F */
    KEY_F6, KEY_F7, KEY_F8, KEY_F9,     /* 0x40 - 0x43 */
    KEY_F10, KEY_NUMLOCK, KEY_SCRLOCK, KEY_KPHOME,  /* 0x44 - 0x47 */
    KEY_KPUP, KEY_KPPGUP, KEY_KPMINUS, KEY_KPLEFT,  /* 0x48 - 0x4B */
    KEY_KPCENTER, KEY_KPRIGHT, KEY_KPPLUS, KEY_KPEND,  /* 0x4C - 0x4F */
    KEY_KPDOWN, KEY_KPPGDN, KEY_KPINSERT, KEY_KPDEL,  /* 0x50 - 0x53 */
    KEY_SYSREQ, KEY_UNKNOWN, '>', KEY_UNKNOWN,  /* 0x54 - 0x57 */
};

unsigned short keyboard_caps[] =
{
    KEY_UNKNOWN, ASCII_ESC, '1', '2',   /* 0x00 - 0x03 */
    '3', '4', '5', '6',                 /* 0x04 - 0x07 */
    '7', '8', '9', '0',                 /* 0x08 - 0x0B */
    '\'', '¡', ASCII_BS, '\t',           /* 0x0C - 0x0F */
    'Q', 'W', 'E', 'R',                 /* 0x10 - 0x13 */
    'T', 'Y', 'U', 'I',                 /* 0x14 - 0x17 */
    'O', 'P', '`', '+',                 /* 0x18 - 0x1B */
    '\n', KEY_LCTRL, 'A', 'S',          /* 0x1C - 0x1F */
    'D', 'F', 'G', 'H',                 /* 0x20 - 0x23 */
    'J', 'K', 'L', 'Ñ',                 /* 0x24 - 0x27 */
    '\'', KEY_UNKNOWN, KEY_LSHIFT, 'Ç',        /* 0x28 - 0x2B */
    'Z', 'X', 'C', 'V',                 /* 0x2C - 0x2F */
    'B', 'N', 'M', ',',                 /* 0x30 - 0x33 */
    '.', '-', KEY_RSHIFT, KEY_PRINTSCRN, /* 0x34 - 0x37 */
    KEY_LALT, ' ', KEY_CAPSLOCK, KEY_F1, /* 0x38 - 0x3B */
    KEY_F2, KEY_F3, KEY_F4, KEY_F5,     /* 0x3C - 0x3F */
    KEY_F6, KEY_F7, KEY_F8, KEY_F9,     /* 0x40 - 0x43 */
    KEY_F10, KEY_NUMLOCK, KEY_SCRLOCK, KEY_KPHOME,  /* 0x44 - 0x47 */
    KEY_KPUP, KEY_KPPGUP, KEY_KPMINUS, KEY_KPLEFT,  /* 0x48 - 0x4B */
    KEY_KPCENTER, KEY_KPRIGHT, KEY_KPPLUS, KEY_KPEND,  /* 0x4C - 0x4F */
    KEY_KPDOWN, KEY_KPPGDN, KEY_KPINSERT, KEY_KPDEL,  /* 0x50 - 0x53 */
    KEY_SYSREQ, KEY_UNKNOWN, '<', KEY_UNKNOWN,  /* 0x54 - 0x57 */
};



inline uint8_t keyboard_read_status(void)
{
	return inport_byte(keyboard_command_port);
}

inline uint8_t keyboard_read_buffer(void)
{
	return inport_byte(keyboard_data_port);
}

void keyboard_send_command(uint8_t command)
{
	keyboard_wait();
	outport_byte(keyboard_command_port, command);
}

int keyboard_send_data(uint8_t data)
{
	uint8_t response = 0;

	keyboard_wait();
	outport_byte(keyboard_data_port, data);

	keyboard_wait();
	response = keyboard_read_buffer();

	if(response == resend)
	{
		for(uint8_t i = 0; i < 3; i++)
		{
			outport_byte(keyboard_data_port, data);
			keyboard_wait();
			response = keyboard_read_buffer();

			if(keyboard_read_buffer() != resend)
				return response;
		}
		return -1;
	}
	else
		return response;
}

bool install_keyboard(void)
{
	uint8_t test = 0;

	if(check_ps2_controller())
	{
		keyboard_flush_buffer();
		test = keyboard_send_data(reset_and_test);
		
		if(test != test_fail || test != test_error)
		{
			install_irq_handler(1, keyboard_handler);
			keyboard_send_data(enable_scanning);
		}
		else
			return false;
	}

	return false;
}

void disable_keyboard(void)
{
	keyboard_send_data(disable_scanning);
}

unsigned char read_key()
{
	static unsigned char key_code, value;

	key_code = keyboard_read_buffer();
	value =  inport_byte(keyboard_ack_port);
	outport_byte(keyboard_ack_port, value | 0x80);
	outport_byte(keyboard_ack_port, value );

	return key_code;
}


void keyboard_handler()
{
	unsigned char scancode = 0;
	unsigned char character = 0;
	key_pressed = false;

	if( ( keyboard_read_status() & keyboard_mask_input_buffer ) == 0)  //Only read a key if there is something to read
	{
		scancode = read_key();

		if( scancode & 0x80) //If a key is released and it was a shit, control ot alt set the mode to false
		{
			switch(keyboard_unshifted[scancode -128])
			{
				case KEY_LSHIFT:
				case KEY_RSHIFT:
					shift = false;
					break;

				case KEY_LCTRL:
				case KEY_RCTRL:
					control = false;
					break;

				case KEY_LALT:
				case KEY_RALT:
					alt = false;
					break;
			}
		}
		else
		{
			key_pressed = true;
			
			switch(keyboard_unshifted[scancode]) //Check the shift, control, caps lock and alt keyd
			{
				case KEY_CAPSLOCK:
					caps_lock = !caps_lock;
					break;
				case KEY_LSHIFT:
				case KEY_RSHIFT:
					shift = true;
					break;
				case KEY_LCTRL:
				case KEY_RCTRL:
					control = true;
					break;
				case KEY_LALT:
				case KEY_RALT:
					alt = true;
					break;
			}
			if(!control || !alt)
			{
				if(shift)
					character = keyboard_shifted[scancode];
				else if(caps_lock)
					character = keyboard_caps[scancode];
				else
					character = keyboard_unshifted[scancode];
			}

			if(buffer_end < 127)
			{
				buffer_end++;
			}
			keyboard_buffer[buffer_end] = character;
		}

	}
}

void reset_buffer(void)
{
	buffer_end = 0;
}

bool kbhit(void)
{
	return key_pressed;
}

unsigned char keyboard_getch()
{
	while(buffer_end == 0); //If there are no key strokes wait until we get one
	disable_interrupts();
	
	for(unsigned char i = 0; i < buffer_end; i++)
	{
		keyboard_buffer[i] = keyboard_buffer[i+1];
	}
	buffer_end--;
	enable_interrupts();

	return keyboard_buffer[0];
}

void keyboard_flush_buffer(void)
{
	uint8_t temp;

	do
	{
		temp = keyboard_read_status();
		if( (temp & keyboard_mask_output_buffer) != 0)
		{
			(void)keyboard_read_buffer();
			continue;
		}
	}while( (temp & keyboard_mask_input_buffer) != 0);
}

bool keyboard_wait(void) //Wait until the keyboard is not busy, if the keyboard is still busy it will return false
{
	for(uint32_t i = 0; i < 1000; i++)
	{
		if( ( keyboard_read_status() & keyboard_mask_input_buffer ) == 0 )
			return true;
	}

	return false;
}