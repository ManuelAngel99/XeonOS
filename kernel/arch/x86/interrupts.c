/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-13 21:03:59
* 
* File: interrupts.c
* Description: Defines the basic interrupt hamdler functions
*/

#include <arch/x86/interrupts.h>
#include <arch/x86/system.h>
#include <kernel/portio.h>
#include <kernel/tty.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>


#define KERNEL_MODE_IDT_FLAG 0x8E
#define USER_MODE_IDT_FLAG 0xEE
#define KERNEL_MODE_CODE_SELECTOR 0x8


extern uint32_t interrupt_handler_table[256];
static void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

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


void setup_interrupts(void)
{
    // Set the special idt_pointer
    idt_pointer.limit = ( sizeof(InterruptDescriptorTableEntry_t) * 256 ) - 1;  // Subsract 1 because sizeof doesn't start from 0
    idt_pointer.base = (uint32_t)&idt;

    // Clear the whole idt to zeros
    memset(&idt, 0, sizeof(InterruptDescriptorTableEntry_t) * 256 );
    for(uint32_t i = 0; i < 256; i++)
    {
        idt_set_gate(i, interrupt_handler_table[i], 0x8, 0x8E);   
    }

    load_idt();
    remap_pics();

}


void remap_pics(void)
{
    outport_byte(master_pic_command, 0x11);
    outport_byte(slave_pic_command, 0x11);

    outport_byte(master_pic_data, 0x20);
    outport_byte(slave_pic_data, 0x28);

    outport_byte(master_pic_data, 0x04);
    outport_byte(slave_pic_data, 0x02);

    outport_byte(master_pic_data, 0x01);
    outport_byte(slave_pic_data, 0x01);

    outport_byte(master_pic_data, 0x0);
    outport_byte(slave_pic_data, 0x0);

}


void irq_set_mask(uint8_t irq)
{
    uint16_t port;
    uint8_t value;

    if(irq < 8)
        port = master_pic_data;
    else
        port = slave_pic_data;

    value = inport_byte(port) | (1 << irq);
    outport_byte(port, value);
}

void irq_clear_mask(uint8_t irq)
{
    uint16_t port;
    uint8_t value;

    if(irq < 8)
        port = master_pic_data;
    else
        port = slave_pic_data;

    value = inport_byte(port) & ~(1 << irq);
    outport_byte(port, value);
}

void exception_handler(StackState_t stack)
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


void irq_handler(StackState_t stack) 
{
    if(irq_routines[stack.interrupt_number - 32])
    {
        void (*handler)(StackState_t) = irq_routines[stack.interrupt_number - 32];  //Void function pointer
        handler(stack);
    }
	
    if(stack.interrupt_number > 39)
		outport_byte(slave_pic_command, 0x20);

	outport_byte(master_pic_command, 0x20);
}

void install_irq_handler(size_t irq_number, void (*handler)(StackState_t stack))
{
    if(irq_number < 16)
        irq_routines[irq_number] = handler;
    else
        return;
}

void uninstall_irq_handler(size_t irq_number)
{
    if(irq_number < 16)
        irq_routines[irq_number] = 0;
    else
        return;
}