/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-13 18:45:33
* 
* File: portio.h
* Description: Defines the basic port comunication functions
*/
#ifndef PORTIO_H
#define PORTIO_H

#ifdef _cplusplus
	extern "C" {
#endif


#include <stdint.h>

void outport_byte(uint16_t port, uint8_t value);
void outport_word(uint16_t port, uint16_t value);
void outport_long(uint16_t port, uint32_t value);

uint8_t inport_byte(uint16_t port);
uint16_t inport_word(uint16_t port);
uint32_t inport_long(uint16_t port);

#ifdef _cplusplus
}
#endif

#endif // PORTIO_H
