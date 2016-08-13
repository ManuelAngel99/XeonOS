/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-13 18:52:07
* 
* File: portio.c
* Description: Implements the basic port communication functions for x86
*/

#include <kernel/portio.h>

void outport_byte(uint16_t port, uint8_t value)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (value));
}

void outport_word(uint16_t port, uint16_t value)
{
    __asm__ __volatile__ ("outw %1, %0" : : "dN" (port), "a" (value));
}

void outport_long(uint16_t port, uint32_t value)
{
    __asm__ __volatile__ ("outl %1, %0" : : "dN" (port), "a" (value));
}

uint8_t inport_byte(uint16_t port)
{
    uint8_t result;

    __asm__ __volatile__("inb %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

uint16_t inport_word(uint16_t port)
{
    uint16_t result;

    __asm__ __volatile__("inw %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

uint32_t inport_long(uint16_t port)
{
    uint32_t result;

    __asm__ __volatile__("inl %1, %0" : "=a" (result) : "dN" (port));
    return result;
}
