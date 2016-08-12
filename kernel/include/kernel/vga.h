/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 11:01:05
* 
* File: vga.h
* Description: Defines some vga utilities so we can use them to output code more easily
*/

#ifndef _K_VGA_H
#define _K_VGA_H

#include <stdint.h>

static const size_t VGA_TERMINAL_HEIGHT = 25;
static const size_t VGA_TERMINAL_WIDTH  = 80;

static uint16_t* const VIDEO_MEMORY = (uint16_t*) 0xB8000;

typedef enum
{
    BLACK     = 0,
    BLUE      = 1,
    GREEN     = 2,
    CYAN      = 3,
    RED       = 4,
    MAGENTA   = 5,
    BROWN     = 6,
    L_GRAY    = 7,
    GRAY      = 8,
    L_BLUE    = 9,
    L_GREEN   = 10,
    L_CYAN    = 11,
    L_RED     = 12,
    L_MAGENTA = 13,
    L_BROWN   = 14,
    WHITE     = 15      
} colours;

/*
    NOTE: Functions declared as static so they are only visible to other functions in the same translation unit (this file and the files who include it)
*/

static inline uint8_t make_color(enum vga_color foreground, enum vga_color background)
{
    return foreground | background << 4;
}

static inline uint16_t make_vgaentry(char character, uint8_t color)
{
    uint16_t character_to_16_bytes = character;
    uint16_t color_to_16_bytes = color;
    return character_to_16_bytes | (color_to_16_bytes << 8);
}



#endif // _K_VGA_H
