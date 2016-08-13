/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-13 20:39:32
* 
* File: idt.c
* Description: Implements the functions needed to setup the idt
*/
#include <arch/i386/idt.h>
#include <kernel/portio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define KERNEL_MODE_IDT_FLAG 0x8E
#define USER_MODE_IDT_FLAG 0xEE
#define KERNEL_MODE_CODE_SELECTOR 0x8



void idt_set_gate(size_t num, uint32_t base, uint16_t code_selector, uint8_t flags)
{
	// Setuo the base address
	idt[num].function_low = (base & 0xFFFF);
	idt[num].function_high = ((base >> 16) & 0xFFFF);

	// Setup the code selector
	idt[num].code_selector = code_selector;

	// Set the reserved byte to 0
	idt[num].reserved_byte = 0;

	// Setup the flags
	idt[num].flags = flags;
}

void remap_pics()
{
	outport_byte(0x20, 0x11);
	outport_byte(0xA0, 0x11);

	outport_byte(0x21, 0x20);
	outport_byte(0xA1, 0x28);

	outport_byte(0x21, 0x04);
	outport_byte(0xA1, 0x02);

	outport_byte(0x21, 0x01);
	outport_byte(0xA1, 0x01);

	outport_byte(0x21, 0x0);
	outport_byte(0xA1, 0x0);
}

extern uint32_t interrupt_handler_table[256];

void setup_idt()
{
	// Set the special idt_pointer
	idt_pointer.limit = ( sizeof(struct InterruptDescriptorTableEntry) * 256 ) - 1;	// Subsract 1 because sizeof doesn't start from 0
	idt_pointer.base = (uint32_t)&idt;

	// Clear the whole idt to zeros
	memset(&idt, 0, sizeof(struct InterruptDescriptorTableEntry) * 256 );
	for(uint32_t i = 0; i < 256; i++)
	{
		idt_set_gate(i, interrupt_handler_table[i], 0x8, 0x8E);   
	}

	load_idt();
	remap_pics();

}