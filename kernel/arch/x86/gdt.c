/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-13 20:03:31
* 
* File: gdt.c
* Description: Implements the necesary functions for setting up the GDT
*/

#include <stdint.h>
#include <stddef.h>
#include <arch/x86/gdt.h>

// Setup a descriptor in the Global Descriptor Table
void gdt_set_gate(size_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    // Setup the descriptor base address
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    // Setup the descriptor limits
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    // Finally, set up the granularity and access flags
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void setup_gdt(void)
{
    //NULL segment, it can be used to hold the GDT address
    gdt_set_gate(0, 0, 0, 0, 0);

    //Kernel mode code
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    //Kerel mode data
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    //User mode code
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    //User mode data
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    gdt_pointer.base = sizeof(GlobalDescriptorTableEntry_t) * 5 - 1; // Subsract 1 because sizeof doesn't start from 0
    gdt_pointer.address = (uint32_t)&gdt;


    // Remove the old GDT and install the new one
    load_gdt();
}