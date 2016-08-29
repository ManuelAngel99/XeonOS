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

//Define the special key modifiers
#define CAPS_KEY 29
#define LEFT_SHIFT 42 
#define RIGHT_SHIFT 54
#define ALT_GR 59

static volatile bool key_pressed, caps_locked;
static unsigned char keyboard_buffer[129];
static volatile unsigned int buffer_end = 0;

static volatile key_t keyboard[105] =
{
	{.is_pressed = false, .regular_print_value = -1,   .shifted_print_value = -1,   .alt_gr_print_value = -1},		// -1
	{.is_pressed = false, .regular_print_value = 'º', .shifted_print_value = 'ª', .alt_gr_print_value = '\\'},	// 1
	{.is_pressed = false, .regular_print_value = '1', .shifted_print_value = '!', .alt_gr_print_value = '|'},	// 2
	{.is_pressed = false, .regular_print_value = '2', .shifted_print_value = '"', .alt_gr_print_value = '@'},	// 3
	{.is_pressed = false, .regular_print_value = '3', .shifted_print_value = '·', .alt_gr_print_value = '#'},	// 4
	{.is_pressed = false, .regular_print_value = '4', .shifted_print_value = '$', .alt_gr_print_value = '~'},	// 5
	{.is_pressed = false, .regular_print_value = '5', .shifted_print_value = '%', .alt_gr_print_value = '5'},	// 6
	{.is_pressed = false, .regular_print_value = '6', .shifted_print_value = '&', .alt_gr_print_value = '6'},	// 7
	{.is_pressed = false, .regular_print_value = '7', .shifted_print_value = '/', .alt_gr_print_value = '{'},	// 8
	{.is_pressed = false, .regular_print_value = '8', .shifted_print_value = '(', .alt_gr_print_value = '['},	// 9
	{.is_pressed = false, .regular_print_value = '9', .shifted_print_value = ')', .alt_gr_print_value = ']'},	// 10
	{.is_pressed = false, .regular_print_value = '-1', .shifted_print_value = '=', .alt_gr_print_value = '}'},	// 11
	{.is_pressed = false, .regular_print_value = '\'',.shifted_print_value = '?', .alt_gr_print_value = '\\'},	// 12
	{.is_pressed = false, .regular_print_value = '¡', .shifted_print_value = '¿', .alt_gr_print_value = -1},		// 13
	{.is_pressed = false, .regular_print_value = '\b',.shifted_print_value = '\b',.alt_gr_print_value = '\b'},	// 14
	{.is_pressed = false, .regular_print_value = '\t',.shifted_print_value = '\t',.alt_gr_print_value = '\t'},	// 15
	{.is_pressed = false, .regular_print_value = 'q', .shifted_print_value = 'Q', .alt_gr_print_value = '@'},	// 16
	{.is_pressed = false, .regular_print_value = 'w', .shifted_print_value = 'W', .alt_gr_print_value = -1},		// 17
	{.is_pressed = false, .regular_print_value = 'e', .shifted_print_value = 'E', .alt_gr_print_value = -1},		// 18
	{.is_pressed = false, .regular_print_value = 'r', .shifted_print_value = 'R', .alt_gr_print_value = -1},		// 19
	{.is_pressed = false, .regular_print_value = 't', .shifted_print_value = 'T', .alt_gr_print_value = -1},		// 20
	{.is_pressed = false, .regular_print_value = 'y', .shifted_print_value = 'Y', .alt_gr_print_value = -1},		// 21
	{.is_pressed = false, .regular_print_value = 'u', .shifted_print_value = 'U', .alt_gr_print_value = -1},		// 22
	{.is_pressed = false, .regular_print_value = 'i', .shifted_print_value = 'I', .alt_gr_print_value = -1},		// 23
	{.is_pressed = false, .regular_print_value = 'o', .shifted_print_value = 'O', .alt_gr_print_value = -1},		// 24
	{.is_pressed = false, .regular_print_value = 'p', .shifted_print_value = 'P', .alt_gr_print_value = -1},		// 25
	{.is_pressed = false, .regular_print_value = '`', .shifted_print_value = '^', .alt_gr_print_value = '['},	// 26
	{.is_pressed = false, .regular_print_value = '+', .shifted_print_value = '*', .alt_gr_print_value = ']'},	// 27
	{.is_pressed = false, .regular_print_value = '\n',.shifted_print_value = '\n',.alt_gr_print_value = '\n'},	// 28
	{.is_pressed = false, .regular_print_value = -1,   .shifted_print_value = -1,   .alt_gr_print_value = -1},		// 29
	{.is_pressed = false, .regular_print_value = 'a', .shifted_print_value = 'A', .alt_gr_print_value = 0},		// 3-1
	{.is_pressed = false, .regular_print_value = 's', .shifted_print_value = 'S', .alt_gr_print_value = -1},		// 31
	{.is_pressed = false, .regular_print_value = 'd', .shifted_print_value = 'D', .alt_gr_print_value = -1},		// 32
	{.is_pressed = false, .regular_print_value = 'f', .shifted_print_value = 'F', .alt_gr_print_value = -1},		// 33
	{.is_pressed = false, .regular_print_value = 'g', .shifted_print_value = 'G', .alt_gr_print_value = -1},		// 34
	{.is_pressed = false, .regular_print_value = 'h', .shifted_print_value = 'H', .alt_gr_print_value = -1},		// 35
	{.is_pressed = false, .regular_print_value = 'j', .shifted_print_value = 'J', .alt_gr_print_value = -1},		// 36
	{.is_pressed = false, .regular_print_value = 'k', .shifted_print_value = 'K', .alt_gr_print_value = -1},		// 37
	{.is_pressed = false, .regular_print_value = 'l', .shifted_print_value = 'L', .alt_gr_print_value = -1},		// 38
	{.is_pressed = false, .regular_print_value = 'ñ', .shifted_print_value = 'Ñ', .alt_gr_print_value = -1},		// 39
	{.is_pressed = false, .regular_print_value = '´', .shifted_print_value = '¨', .alt_gr_print_value = '{'},	// 40
	{.is_pressed = false, .regular_print_value = 'ç', .shifted_print_value = 'Ç', .alt_gr_print_value = '}'},	// 41
	{.is_pressed = false, .regular_print_value = -1,   .shifted_print_value = -1,   .alt_gr_print_value = -1},		// 42
	{.is_pressed = false, .regular_print_value = '<', .shifted_print_value = '>', .alt_gr_print_value = '|'},	// 43
	{.is_pressed = false, .regular_print_value = 'z', .shifted_print_value = 'Z', .alt_gr_print_value = -1},		// 44
	{.is_pressed = false, .regular_print_value = 'x', .shifted_print_value = 'X', .alt_gr_print_value = -1},		// 45
	{.is_pressed = false, .regular_print_value = 'c', .shifted_print_value = 'C', .alt_gr_print_value = -1},		// 46
	{.is_pressed = false, .regular_print_value = 'v', .shifted_print_value = 'V', .alt_gr_print_value = -1},		// 47
	{.is_pressed = false, .regular_print_value = 'b', .shifted_print_value = 'B', .alt_gr_print_value = -1},		// 48
	{.is_pressed = false, .regular_print_value = 'n', .shifted_print_value = 'N', .alt_gr_print_value = -1},		// 49
	{.is_pressed = false, .regular_print_value = 'm', .shifted_print_value = 'M', .alt_gr_print_value = -1},		// 50
	{.is_pressed = false, .regular_print_value = ',', .shifted_print_value = ';', .alt_gr_print_value = -1},		// 51
	{.is_pressed = false, .regular_print_value = '.', .shifted_print_value = ':', .alt_gr_print_value = -1},		// 52
	{.is_pressed = false, .regular_print_value = '-', .shifted_print_value = '·', .alt_gr_print_value = -1},		// 53
	{.is_pressed = false, .regular_print_value = -1,   .shifted_print_value = -1,   .alt_gr_print_value = -1},		// 55
	{.is_pressed = false, .regular_print_value = -1,   .shifted_print_value = -1,   .alt_gr_print_value = -1},		// 56
	{.is_pressed = false, .regular_print_value = -1,   .shifted_print_value = -1,   .alt_gr_print_value = -1},		// 57
	{.is_pressed = false, .regular_print_value = ' ', .shifted_print_value = ' ', .alt_gr_print_value = -1},		// 58

};



uint16_t key_map_es[] =
{
	0, 63, 2, 3, 4,				//0 - 4
	5, 6, 7, 8, 9,				//5 - 9
	10, 11, 12, 13, 14,			//10 - 14
	15, 16, 17, 18, 19,			//15 - 19
	20, 21, 22, 23, 24,			//20 - 24
	25, 26, 27, 28, 55,			//25 - 29
	30, 31, 32, 33, 34,			//30 - 34
	35, 36, 37, 38, 39,			//35 - 39
	40,  1, 42, 43, 44,			//40 - 44
	45, 46, 47, 48, 49,			//45 - 49
	50, 51, 52, 53, 54,			//50 - 54
	79, 59, 58, 29, 64,			//55 - 59
	65, 66, 67, 68,	69,			//60 - 64
	70, 71, 72, 73, 88,			//65 - 69
	80, 92, 93, 94, 91,			//70 - 74
	96, 97, 98, 95, 99,			//75 - 79
	100, 101, 103, 104, 0,		//80 - 84
	0, 43, 74, 75, 0,			//85 - 89
	0, 56, 60, 61, 0,			//90 - 94
	0, 0, 0, 0, 0,				//95 - 99
	0, 0, 0, 0, 0				//100 - 104
};


/*static void keyboard_send_command(uint8_t command); Not used for now*/ 
static int keyboard_send_data(uint8_t data);
static void keyboard_flush_buffer(void);
static bool keyboard_wait(void);


static inline uint8_t keyboard_read_status(void)
{
	return inport_byte(keyboard_command_port);
}

static inline uint8_t keyboard_read_buffer(void)
{
	return inport_byte(keyboard_data_port);
}
/** Not used for now
*
static void keyboard_send_command(uint8_t command)
{
	keyboard_wait();
	outport_byte(keyboard_command_port, command);
}*/

static int keyboard_send_data(uint8_t data)
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


static void keyboard_flush_buffer(void)
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

static bool keyboard_wait(void) //Wait until the keyboard is not busy, if the keyboard is still busy it will return false
{
	for(uint32_t i = 0; i < 1000; i++)
	{
		if( ( keyboard_read_status() & keyboard_mask_input_buffer ) == 0 )
			return true;
	}

	return false;
}

bool install_keyboard(void)
{
	uint8_t test = 0;

	// Init all the non printable keys
	for(uint8_t i = 59; i < 105; i++)
	{
		keyboard[i].is_pressed = false;
		keyboard[i].regular_print_value = -1;
		keyboard[i].shifted_print_value = -1;
		keyboard[i].alt_gr_print_value  = -1;
	}
	//Init the caps
	caps_locked = false;

	// Test if the keyboard is avaliable
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

static unsigned char read_key()
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

	if( ( keyboard_read_status() & keyboard_mask_input_buffer ) == 0)  //Only read a key if there is something to read
	{
		scancode = read_key();
		
		if((scancode & 0x80))
			keyboard[ key_map_es[scancode - 128] ].is_pressed = false;
		else
		{
			key_pressed = true;
			keyboard[ key_map_es[scancode] ].is_pressed = true;

			//Invert the caps lock
			if( keyboard[CAPS_KEY].is_pressed)
				caps_locked = !caps_locked;

			if( keyboard[ key_map_es[scancode] ].regular_print_value >= 0)
			{
				if(buffer_end < 127)
					buffer_end++;
				
				if ( keyboard[LEFT_SHIFT].is_pressed || keyboard[RIGHT_SHIFT].is_pressed || caps_locked)
					keyboard_buffer[buffer_end] = keyboard[ key_map_es[scancode] ].shifted_print_value;
				else if ( keyboard[ALT_GR].is_pressed )
					keyboard_buffer[buffer_end] = keyboard[ key_map_es[scancode] ].alt_gr_print_value;
				else
					keyboard_buffer[buffer_end] = keyboard[ key_map_es[scancode] ].regular_print_value;
			}
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

uint16_t keyboard_getch()
{
	while(buffer_end == 0); //If there are no key strokes wait until we get one
	disable_interrupts();
	
	// Move all the keystrokes in the buffer
	for(unsigned char i = 0; i < buffer_end; i++)
		keyboard_buffer[i] = keyboard_buffer[i+1];

	buffer_end--;
	enable_interrupts();

	return keyboard_buffer[0];
}