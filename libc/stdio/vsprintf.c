/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-09-02 11:59:23
* 
* File: vsprintf.c
* Description: Implements the vsprintf function wich returns a string formatted with the data provided in an argument list
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <macros.h>

typedef struct FlagPair
{
	char string[3], flag;
}FlagPair_t;

static FlagPair_t format_modifiers[] =
{
	{ "-", 0x1},		// Left justify flag
	{ "+", 0x2},		// Leading plus flag
	{ " ", 0x4},		// Leading space flag
	{ "#", 0x8},		// Alternate form flag
	{ "0", 0x10}		// Pad with zeros flag
};

static FlagPair_t data_modifiers[] =
{
	{ "hh", 0x1},
	{ "h", 0x2},
	{ "l", 0x4},
	{ "ll", 0x8},
	{ "j", 0x10},
	{ "z", 0x20},
	{ "L", 0x40}
};

static void adjust_size(char* buffer, char format_flags, int min_width);
static void pad_with(char* string, char pad_character, int lenght, bool at_the_beggining);
void format_number(char* buffer, short format_flags, int min_width, int precission, int base , bool integer ,bool uppercase);

inline static bool has_sign_char(char* string)
{
	return (string[0] == '+' || string[0] == '-');
}


int	vsprintf(char* buffer, const char* format, va_list arguments)
{
	int count = 0, min_width, precission, base, auxiliar;
	char format_flags, data_flags, data_specifier[4], print_buffer[200];
	bool dot_pressent, uppercase;
	size_t i;
	
	memset(buffer, 0, strlen(buffer));
	memset(data_specifier, 0, strlen(data_specifier));
	
	for(; *format;)
	{
		if(*format == '%')
		{
			format_flags = data_flags = base = auxiliar = dot_pressent = uppercase = 0;
			min_width = precission = -1;
			memset(print_buffer, 0, 100);
			
			//Advance a char
			format++;
			
			for(; *format; format++)
			{
				if(strchr( "csdioxXufFeEaAgGnp%", *format ) != NULL)
					break;
				
				//Set the format modifier flags
				if(*format == format_modifiers[0].string[0])
					set_flag(format_flags, format_modifiers[0].flag );
				else if(*format == format_modifiers[1].string[0])
					set_flag(format_flags, format_modifiers[1].flag );
				else if(*format == format_modifiers[2].string[0])
					set_flag(format_flags, format_modifiers[2].flag );
				else if(*format == format_modifiers[3].string[0])
					set_flag(format_flags, format_modifiers[3].flag );
				else if(*format == format_modifiers[4].string[0])
					set_flag(format_flags, format_modifiers[4].flag );
				
				//If a * is found in the format string its value is pulled from the va_list
				else if(*format == '*')
				{
					auxiliar = va_arg(arguments, int);
					if(dot_pressent)
						precission = auxiliar;
					else
						min_width = auxiliar;
				}
				else if(*format == '.')
					dot_pressent = true;
				else if(isdigit(*format))
				{
					auxiliar = strtol(format, (char**)&format, 10);
					format--;
					if(dot_pressent)
						precission = auxiliar;
					else
						min_width = auxiliar;
				}
				
				//Search data modifiers
				else if(isalpha(*format))
				{
					for(i = 0; strchr( "hljztL", *format ) != NULL; strncat(data_specifier, format, 1) ,format++ , i++);
					format--;

					//Check each data modifier to se if there is a match
					for(size_t j = 0; j < 8; j++)
						if(strncmp(data_specifier, data_modifiers[j].string, i) == 0)
						{
							set_flag(data_flags, data_modifiers[j].flag);
							break;
						}

				}
				else
					return -1;
			}
			
			//Now process each data type specifier
			//Note that wchar_t is not supported
			
			if(*format == 'c')
				print_buffer[0] = (char)va_arg(arguments, int);
			
			else if(*format == 's')
			{
				strcat(print_buffer, va_arg(arguments, char*));
				if(precission != -1)
					print_buffer[precission - 1] = 0;
					
				adjust_size(print_buffer, format_flags, min_width);
			}
			
			else if(strchr("dioxXu", *format) != NULL)
			{
				switch(*format)
				{

					case 'd':
					case 'i':
						base = -10;
						break;
					case 'o':
						base = 8;
						break;
					case 'x':
						base = 16;
						break;
					case 'X':
						base = 16;
						uppercase = true;
						break;
					case 'u':
						base = 10;
						break;
				}
				
				if( data_flags == 0 )
					lltoa( va_arg(arguments, int), print_buffer, base );
				else if( check_flag(data_flags, data_modifiers[0].flag))
					lltoa( (char)va_arg(arguments, int), print_buffer, base );
				else if( check_flag(data_flags, data_modifiers[1].flag))
					lltoa( (short)va_arg(arguments, int), print_buffer, base );
				else if( check_flag(data_flags, data_modifiers[2].flag))
					lltoa( va_arg(arguments, long), print_buffer, base );
				else if( check_flag(data_flags, data_modifiers[3].flag))
					lltoa( va_arg(arguments, long long), print_buffer, base );
				else if( check_flag(data_flags, data_modifiers[4].flag))
					lltoa( va_arg(arguments, intmax_t), print_buffer, base );
				else if( check_flag(data_flags, data_modifiers[5].flag))
					lltoa( va_arg(arguments, size_t), print_buffer, base );
				else
					return -1;

				format_number(print_buffer, format_flags, min_width, precission, base, false, uppercase );

			}
			
			else if(strchr("fFeE", *format) != NULL)
			{
				bool exponent_notation = false;
				switch(*format)
				{
					case 'F':
						uppercase = true;
					case 'E':
						uppercase = true;
					case 'e':
						exponent_notation = true;
						break;
					default:
						break;
				}
				
				if(precission == -1)
					precission = 6;
				
				if( data_flags == 0 || check_flag(data_flags, data_modifiers[2].flag))
					ldtoa( va_arg(arguments, double), print_buffer, precission, exponent_notation);
				else if( check_flag(data_flags, data_modifiers[6].flag))
					ldtoa( va_arg(arguments, long double), print_buffer, precission, exponent_notation);
					
				format_number(print_buffer, format_flags, min_width, precission, base, (*format != 'e' || *format != 'E'), uppercase );


			}
			
			else if(*format == 'p')
			{
				lltoa( (int)va_arg(arguments, void*), print_buffer, 16);
				format_number(print_buffer, format_flags, min_width, precission, base, false, uppercase );
			}
			
			strcat(buffer, print_buffer);
			count += strlen(print_buffer);
			buffer = buffer + strlen(print_buffer);
			format++;
		}
		else
		{
			*buffer = *format;
			buffer++;
			count++;
			format++;
		}
		//Make sure that the string ends with a null char
		*buffer = 0;
	}

	return count;
}

void format_number(char* buffer, short format_flags, int min_width, int precission, int base , bool integer ,bool uppercase)
{
	//Append a + if the number is positive
	if( check_flag(format_flags, format_modifiers[1].flag) && !has_sign_char(buffer) )
		pad_with(buffer, '+', 1, true);
	

	//Pad with zeros if not enough precission
	if( precission > (int)strlen(buffer) )
	{
		char padding = precission - strlen(buffer);
		if(has_sign_char(buffer))
			pad_with(buffer + 1, '0', ++padding, integer);
		else
			pad_with(buffer , '0', padding, integer);
	}
	
	//Append a blank space at the beggining of the string if there is no sign characeter
	if( check_flag(format_flags, format_modifiers[2].flag) && !has_sign_char(buffer))
		pad_with(buffer, ' ', 1, true);
	
	//Adjust the size of the string
	adjust_size(buffer, format_flags, min_width);
	
	//Append a 0x to the bool numbers
	if( check_flag(format_flags, format_modifiers[3].flag) && base == 16 )
	{
		pad_with(buffer, 'x', 1, true);
		pad_with(buffer, '0', 1, true);
	}
	
	if(uppercase)
		string_to_upper(buffer);
}

static void adjust_size(char* buffer, char format_flags, int min_width)
{
	if( min_width > (int)strlen(buffer) )
	{
		char pad_char = ' ';
		if(!check_flag(format_flags, format_modifiers[0].flag) && check_flag(format_flags, format_modifiers[4].flag))
			pad_char = '0';
		pad_with(buffer, pad_char, min_width - strlen(buffer), !check_flag(format_flags, format_modifiers[0].flag));
	}
}

//Add a char set at the beggining or at the end of a string
static void pad_with(char* string, char pad_character, int lenght, bool at_the_beggining)
{
	int str_lenght = strlen(string), i;
	if(at_the_beggining)
	{
		for(i = strlen(string); i >= 0; i--)
			string[i + lenght] = string[i];
	
		memset(string, pad_character, lenght);
	}
	else
	{
		for(i = 0; i < lenght; i++)
			string[str_lenght + i] = pad_character;
		
		string[str_lenght + i] = 0;
	}
}
