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

#include <stddef.h>
#include <stdint.h>

struct stack_state
{
	uint32_t ds;										// Saved data segment
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;  // Pushed by 'pusha' 
	uint32_t interrupt_number ,error_code;			// Pushed in the interrupt handler
	uint32_t eip, cs, eflags;							// Pushed by the processor
}__attribute__((packed));

void install_irq_handler(size_t irq_number, void (*handler)(struct stack_state stack));
void uninstall_irq_handler(size_t irq_number);

/* NOTE: BOTH TAKE A STACK_STATE VARIABLE*/
void exception_handler(struct stack_state stack);
void irq_handler(struct stack_state stack);

#endif // INTERRUPTS_H
