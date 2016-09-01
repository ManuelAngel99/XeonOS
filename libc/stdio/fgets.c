/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-01 12:28:07 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-01 12:42:01
 * 
 * Description: Implements the fgets fucntion that returns a string from a file stream
 */

#include <stdio.h>

char* fgets(char* destination_buffer, size_t max_chars, FILE* file_stream)
{
    int character;
    char* destination_pointer;

    //Read max chars from file_stream
    for(destination_pointer = destination_buffer, max_chars--; max_chars > 0; max_chars--)
    {
        if( (character = fgetc(file_stream)) == EOF)
            break;
        *destination_pointer++ = character;
        if(character == '\n')
            break;
    }

    *destination_pointer = 0;
	if (destination_pointer == destination_buffer || character == EOF)
		return NULL;

    return destination_pointer;
}