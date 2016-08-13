/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-13 20:35:03
* 
* File: idt.h
* Description: Defines the stack state structure and some functions to set up the idt
*/

#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include <stddef.h>

/*
    IDT ENTRY LAYOUT:
    Bits:   Description:
    0-15	Lower 16 bits of the function pointer	
    16-31	Code selector, the kernel segment goes here
    32-39	Unused byte, always set to 0
    40-47	Flags -> When calling from the kernel code its value will be 0x8E
    47-63	Upper 16 bits of the funciton pointer
    
*/

struct InterruptDescriptorTableEntry
{
	uint16_t	function_low;
	uint16_t	code_selector;
	uint8_t 	reserved_byte;
	uint8_t	flags;
	uint16_t	function_high;	
}__attribute__((packed));

struct InterruptDescriptorPointer
{
	uint16_t limit;	//The total size of the IDT table
	uint32_t base;	//The address of the first IDT entry
}__attribute__((packed));


struct InterruptDescriptorTableEntry idt[256];
struct InterruptDescriptorPointer idt_pointer;

void idt_set_gate(size_t num, uint32_t base, uint16_t code_selector, uint8_t flags);
void setup_idt(void);
void load_idt(void);


#endif // IDT_H