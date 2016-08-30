/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-22 15:07:32
* 
* File: kbhit.c
* Description: Implementation of the kbhit function wich returns 1 if a key is pressed
*/

#include <stdio.h>

#if defined (__is_xeonos_kernel)
#include <devices/keyboard.h>
#endif


char kbhit(void)
{
#if defined (__is_xeonos_kernel)
    return keyboard_get_key_pressed();
#else
    return 0;
#endif
}