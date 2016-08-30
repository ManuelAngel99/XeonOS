/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 16:44:00
* 
* File: getc.c
* Description: Implements the C standard getchar function wich returns the first character
* in the wrote line and doesn't print the input
*/

#include <stdio.h>

int getc(void)
{
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

        buffer[current_pos] = getch();
    }

    return buffer[1];

}