/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 16:44:00
* 
* File: getchar.c
* Description: Implements the C standard getchar function wich returns the first character in the wrote line
*/

#include <stdio.h>
#include <string.h>

#if defined (__is_xeonos_kernel)
#include <devices/keyboard.h>
#endif

int getchar(void)
{
#if defined(__is_xeonos_kernel)
    int current_pos = 0, buffer[2];
   
    //Make sure that we don't skip the first iteration
    buffer[0] = -1;

    while(buffer[current_pos] != '\n')
    {
        if(buffer[current_pos] == '\b')
        {
            if(current_pos > 1)
                current_pos--;
        }
        else
            if(current_pos < 2 )
                current_pos++;

        buffer[current_pos] = keyboard_getch();
        printf("%c", buffer[current_pos]);
    }

    return buffer[1];
#else
	//TODO: IMPLEMENT A SYSTEM CALL
#endif
	return -1;
}