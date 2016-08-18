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


#define KEY_SPECIAL_FLAG 0x0100
#define KEY_KEYPAD_FLAG  0x0200
#define KEY_SHIFT_FLAG   0x1000
#define KEY_ALT_FLAG     0x2000
#define KEY_CTRL_FLAG    0x4000
#define KEY_RELEASE_FLAG 0x8000

/*
 * Special key codes
 */
#define _SPECIAL(num) (KEY_SPECIAL_FLAG | (num))
#define KEY_UNKNOWN _SPECIAL(0)
#define KEY_F1      _SPECIAL(1)
#define KEY_F2      _SPECIAL(2)
#define KEY_F3      _SPECIAL(3)
#define KEY_F4      _SPECIAL(4)
#define KEY_F5      _SPECIAL(5)
#define KEY_F6      _SPECIAL(6)
#define KEY_F7      _SPECIAL(7)
#define KEY_F8      _SPECIAL(8)
#define KEY_F9      _SPECIAL(9)
#define KEY_F10     _SPECIAL(10)
#define KEY_F11     _SPECIAL(11)
#define KEY_F12     _SPECIAL(12)
#define KEY_LCTRL   _SPECIAL(13)
#define KEY_RCTRL   _SPECIAL(14)
#define KEY_LSHIFT  _SPECIAL(15)
#define KEY_RSHIFT  _SPECIAL(16)
#define KEY_LALT    _SPECIAL(17)
#define KEY_RALT    _SPECIAL(18)
#define KEY_PRINTSCRN _SPECIAL(19)
#define KEY_CAPSLOCK _SPECIAL(20)
#define KEY_NUMLOCK _SPECIAL(21)
#define KEY_SCRLOCK _SPECIAL(22)
#define KEY_SYSREQ  _SPECIAL(23)

/*
 * Keypad keys
 */
#define KEYPAD_START 128
#define _KEYPAD(num) (KEY_KEYPAD_FLAG | KEY_SPECIAL_FLAG | (num+KEYPAD_START))
#define KEY_KPHOME  _KEYPAD(0)
#define KEY_KPUP    _KEYPAD(1)
#define KEY_KPPGUP  _KEYPAD(2)
#define KEY_KPMINUS _KEYPAD(3)
#define KEY_KPLEFT  _KEYPAD(4)
#define KEY_KPCENTER _KEYPAD(5)
#define KEY_KPRIGHT _KEYPAD(6)
#define KEY_KPPLUS  _KEYPAD(7)
#define KEY_KPEND   _KEYPAD(8)
#define KEY_KPDOWN  _KEYPAD(9)
#define KEY_KPPGDN  _KEYPAD(10)
#define KEY_KPINSERT _KEYPAD(11)
#define KEY_KPDEL   _KEYPAD(12)

/*
 * ASCII codes for which there is no convenient C representation
 */
#define ASCII_ESC 0x1B
#define ASCII_BS  0x08



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

bool install_keyboard(void);
void disable_keyboard(void);

void keyboard_send_command(uint8_t command);
int keyboard_send_data(uint8_t data);
void keyboard_flush_buffer(void);
bool keyboard_wait(void);

void keyboard_handler();
void reset_buffer(void);
bool kbhit(void);
unsigned char keyboard_getch(void);

#ifdef _cplusplus
}
#endif


#endif // KEYBOARD_H
