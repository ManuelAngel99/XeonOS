/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-15 16:44:48
* 
* File: keyboard.h
* Description: 
*/
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

#ifdef _cplusplus
    extern "C" {
#endif

/* KEYBOARD STATUS REGISTER:
	Bit 0: Output Buffer Status
		0: Output buffer empty, dont read yet
		1: Output buffer full, please read me :)
	Bit 1: Input Buffer Status
		0: Input buffer empty, can be written
		1: Input buffer full, dont write yet
	Bit 2: System flag
		0: Set after power on reset
		1: Set after successfull completion of the keyboard controllers self-test (Basic Assurance Test, BAT)
	Bit 3: Command Data
		0: Last write to input buffer was data (via port 0x60)
		1: Last write to input buffer was a command (via port 0x64)
	Bit 4: Keyboard Locked
		0: Locked
		1: Not locked
	Bit 5: Auxiliary Output buffer full
		PS/2 Systems:
			0: Determins if read from port 0x60 is valid If valid, 0=Keyboard data
			1: Mouse data, only if you can read from port 0x60
		AT Systems:
			0: OK flag
			1: Timeout on transmission from keyboard controller to keyboard. This may indicate no keyboard is present.
	Bit 6: Timeout
		0: OK flag
		1: Timeout
		PS/2:
			General Timeout
		AT:
			Timeout on transmission from keyboard to keyboard controller. Possibly parity error (In which case both bits 6 and 7 are set)
	Bit 7: Parity error
		0: OK flag, no error
		1: Parity error with last byte
*/
enum keyboard_control_status_masks
{ 
	keyboard_mask_output_buffer		=	1,			//00000001
	keyboard_mask_input_buffer		=	2,			//00000010
	keyboard_mask_system			=	4,			//00000100
	keyboard_mask_command_data		=	8,			//00001000
	keyboard_mask_locked			=	0x10,		//00010000
	keyboard_mask_auxiliar_buffer	=	0x20,		//00100000
	keyboard_mask_timeout			=	0x40,		//01000000
	keyboard_mask_parity			=	0x80		//10000000
};

enum keyboard_commands
{
	set_leds		= 0xED,
	echo			= 0xEE,
	scan_code		= 0xF0,
	identify_kbd	= 0xF2,
	telematics		= 0xF3,
	enable_scanning = 0xF4,
	disable_scanning= 0xF5,
	default_params  = 0xF6,
	set_autorepeat  = 0xF7,
	set_make_release= 0xF8,
	set_make_only   = 0xF9,
	set_all_to_all  = 0xFA,
	set_key_telematic=0xFB,
	set_key_make_rel= 0xFC,
	set_key_make_only=0xFD,
	resend_last_byte =0xDE,
	reset_and_test  = 0xFF
};

enum keyboard_responses
{
	ack		 = 0xFA,
	resend 	 = 0xFE,
	test_ok  = 0xAA,
	test_fail= 0xFC,
	test_error=0xFD
};

typedef struct key
{
	bool is_pressed;
	int16_t regular_print_value;
	int16_t shifted_print_value;
	int16_t alt_gr_print_value;

}key_t;

bool install_keyboard(void);
void disable_keyboard(void);

void keyboard_handler();
void reset_buffer(void);
bool kbhit(void);
uint16_t keyboard_getch(void);

#ifdef _cplusplus
}
#endif


#endif // KEYBOARD_H
