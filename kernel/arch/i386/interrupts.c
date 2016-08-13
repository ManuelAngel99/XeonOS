/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-13 21:03:59
* 
* File: interrupts.c
* Description:
*/
#include <kernel/interrupts.h>
#include <arch/i386/idt.h>
#include <kernel/portio.h>
#include <kernel/tty.h>
#include <stdio.h>

char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void exception_handler(struct stack_state stack)
{
	terminal_clear_screen();
	printf("OOPS! AN INTERNAL ERROR HAS OCURRED!: %s\n", exception_messages[stack.interrupt_number] );
	printf("INTERRUPT NUMBER %x\n", (unsigned int)stack.interrupt_number);	

	printf("EIP %x\n", (unsigned int)stack.eip );
	printf("CS %x\n", (unsigned int)stack.cs );	
	printf("EFLAGS %x\n", (unsigned int)stack.eflags );	
	printf("ERROR CODE %x\n", (unsigned int)stack.error_code );
	printf("DATA SEGMENT %x\n\n",(unsigned int) stack.ds );

	printf("REGISTER EAX %x\n", (unsigned int)stack.eax );
	printf("REGISTER EBX %x\n", (unsigned int)stack.ebx );
	printf("REGISTER ECX %x\n", (unsigned int)stack.ecx );
	printf("REGISTER EDX %x\n", (unsigned int)stack.edx );
	printf("REGISTER ESP %x\n", (unsigned int)stack.esp );
	printf("REGISTER EBP %x\n", (unsigned int)stack.ebp );
	printf("REGISTER EDI %x\n", (unsigned int)stack.edi );
	printf("REGISTER ESI %x\n\n", (unsigned int)stack.esi );

}


void irq_handler(struct stack_state stack) 
{
	terminal_gotoxy(40,0);
	printf("INTERRUPT %d",(unsigned int)stack.interrupt_number);
	if(stack.interrupt_number > 39)
	{
		outport_byte(0xA0, 0x20);
	}
	outport_byte(0x20, 0x20);
}