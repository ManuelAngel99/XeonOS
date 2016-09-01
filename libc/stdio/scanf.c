/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 15:44:00
* 
* File: scanf.c
* Description: Implements the C standard scanf function
*/

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ISSPACE " \t\n\r\f\v"

static int vfscanf(FILE *, const char*, va_list);
static int vsscanf(const char*, const char*, va_list);


int scanf(const char* restrict format, ...)
{
	va_list list;
	va_start(list, format);
	int result = vfscanf(stdin ,format, list);
	va_end(list);
	return result;
}



int fscanf(FILE* file_pointer, const char *format, ...)
{
    int count;
    va_list parameters_to_read;
    
    //Start the parameter list
    va_start(parameters_to_read, format);

    //Read the parameters from a file
    count = vfscanf(file_pointer, format, parameters_to_read);

    //End the parameters list
    va_end(parameters_to_read);

    return count;
}

int sscanf(const char* buffer, const char* format, ...)
{
    int count;
    va_list parameters_to_read;
    
    //Start the parameter list
    va_start(parameters_to_read, format);

    //Read the parameters from the buffer string
    count = vsscanf(buffer, format, parameters_to_read);
    
    //End the parameter list
    va_end(parameters_to_read);

    return count;
}

static int  vfscanf(FILE * file_pointer, const char* format, va_list arguments_to_read)
{
    char buffer[BUFSIZ + 1];
    int count = 0;

    if( fgets(buffer, BUFSIZ, file_pointer) == 0 )
        return -1;
    else
        count = vsscanf(buffer, format, arguments_to_read);

    return count;
}



static int vsscanf (const char* buffer, const char* format, va_list arguments_to_read)
{
    int count, noassign, width, base, lflag;
    const char* tc;
    char *t, tmp[BUFSIZ];

    count = noassign = width = lflag = 0;

    //Loop until there is nothing to scan or there isn't a format specifier
    while(*buffer && *format)
    {
        //Don't compute the spaces
        while(isspace(*format))
            format++;
        
        if(*format == '%')
        {   
            //Get the next char in the format
            format++;
            
            //Loop trough the format string until a format specifier is met
            for(; *format; format++)
            {
                //If a format speficier is met stop the search
                if( strchr( "%bcdefgiosux" , *format) )
                    break;
                if(*format == '*')
                    noassign = 1;
                else if(*format == 'l' || *format == 'L' )
                    lflag = 1;
                else if(*format >= '1' || *format <= '9')
                {
                    //Get the all the digits before the format specifier
                    for(tc = format; isdigit(*format); format++);

                    //Copy those digits to tmp
                    strncpy(tmp, tc, format - tc);
                    tmp[format - tc] = '\0';

                    //Translate from ascii to a int
                    atob((size_t*)&width, tmp, 10);
                    format--;
                }
            }

            //Treat the strings
            if(*format == 's')
            {
                //Skip the spaces before the string
                while(isspace(*buffer))
                    buffer++;
                //If no read width is specified read until the next space
                if(!width)
                    width = strcspn(buffer, ISSPACE);
                
                //If no '*' specified that this shouldn't be read
                if(!noassign)
                {
                    strncpy( t = va_arg( arguments_to_read, char*), buffer, width);
                    t[width] = '\0';
                }
                buffer += width;
            }
            else if(*format == 'c')
            {
                //If no read width is specified read 1 char
                if(!width)
                    width = 1;

                if(!noassign)
                {
                    strncpy( t = va_arg( arguments_to_read, char*), buffer, width);
                    t[width] = '\0';
                }
                buffer += width;
            }
            else if( strchr( "bdoux" , *format) )
            {
                //Skip the spaces before the number
                while(isspace(*buffer))
                    buffer++;

                //Set the base for the number
                switch(*format)
                {
                    case 'x':
                        base = 16;
                        break;
                    case 'o':
                        base = 8;
                        break;
                    case 'b':
                        base = 2;
                        break;
                    default:
                        base = 10;
                        break;
                }

                //Set the width to read
                if(!width)
                {
                    //If there is a space behind the specifier (ex: '%d ') read until a space is found, ele read until the next char is found
                    if(isspace (*(format + 1)) || *(format + 1) == 0)
                        width = strcspn(buffer, ISSPACE);
                    else 
                        width = strchr(buffer, *(format + 1)) - buffer;
                }
                strncpy(tmp, buffer, width);
                tmp[width] = '\0';
                buffer += width;

                if(!noassign)
                    atob(va_arg(arguments_to_read, uint32_t*), tmp, base);
            }
            if(!noassign)
                count++;
            width = noassign = lflag = 0;
        }
        else
        {
            while( isspace(*buffer) )
                buffer++;
            if(*format != *buffer)
                break;
            else
                format++, buffer++;
        }
    }
    return count;
}