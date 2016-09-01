/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-29 23:07:32
* 
* File: getline.c
* Description: Implementation of the getline function that takes a line of text and stores it an a buffer
*/
#include <stdio.h>
#include <macros.h>

int getline(char* output_buffer, size_t* lenght)
{
    int current_pos = -1, current_char = -1;
    
    //If any of these is true we cannot perform the read
    if(*lenght == 0 || output_buffer == NULL || lenght == NULL)
        return -1;

    //Get chars until enter is pressed
    while(current_char != '\n')
    {
        current_char = getch();
        if(current_char == '\b')
        {
            if(current_pos >= 0)
            {
                current_pos--;
                printf("\b");
            }
        }
        else
        {
            if(current_pos < (int)*lenght)
            {
                current_pos++;
                output_buffer[current_pos] = current_char;
            }
            printf("%c", current_char);
        }
    }
    output_buffer[ min( (int)*lenght, current_pos) ] = '\0';

    return current_pos;
}