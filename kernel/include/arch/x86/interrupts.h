/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-13 21:00:47
* 
* File: interrupts.h
* Description: Defines the exception_handler and the irq_handler functions
*/

#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#ifdef _cplusplus
    extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

/*
    IDT ENTRY LAYOUT:
    Bits:   Description:
    0-15	Lower 16 bits of the function pointer	
    16-31	Code selector, the kernel segment goes here
    32-39	Unused byte, always set to 0
    40-47	Flags -> When calling from the kernel code its value will be 0x8E
    47-63	Upper 16 bits of the funciton pointer
    
*/

typedef struct InterruptDescriptorTableEntry
{
	uint16_t	function_low;
	uint16_t	code_selector;
	uint8_t 	reserved_byte;
	uint8_t		flags;
	uint16_t	function_high;	
}__attribute__((packed)) InterruptDescriptorTableEntry_t;

typedef struct InterruptDescriptorPointer
{
	uint16_t limit;	//The total size of the IDT table
	uint32_t base;	//The address of the first IDT entry
}__attribute__((packed)) InterruptDescriptorPointer_t;

typedef struct StackState
{
	uint32_t ds;										// Saved data segment
	uint32_t edi, esi, ebp, useless_esp, ebx, edx, ecx, eax;  // Pushed by 'pusha' 
	uint32_t interrupt_number ,error_code;			// Pushed in the interrupt handler
	uint32_t eip, cs, eflags;							// Pushed by the processor
}__attribute__((packed)) StackState_t;



InterruptDescriptorTableEntry_t idt[256];
InterruptDescriptorPointer_t idt_pointer;

void idt_set_gate(size_t num, uint32_t base, uint16_t code_selector, uint8_t flags);
void load_idt(void);
void remap_pics(void);

void irq_set_mask(uint8_t irq);
void irq_clear_mask(uint8_t irq);


void install_irq_handler(size_t irq_number, void (*)(StackState_t *stack));
void uninstall_irq_handler(size_t irq_number);

void exception_handler(StackState_t stack);
void irq_handler(StackState_t stack);

inline void disable_interrupts(void)
{
    __asm__ __volatile__("cli");
}

inline void enable_interrupts(void)
{
    __asm__ __volatile__("sti");
}

#ifdef _cplusplus
}
#endif

#endif // INTERRUPTS_H
