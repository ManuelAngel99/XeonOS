/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-30 13:13:16
* 
* File: strtok.c
* Description: Splits a string into tokens,
* if str is NULL the function will search in the
* previous string
*/

#include <string.h>

char* strtok(char* str, const char* tokens)
{
	static char* pointer = 0;

	if(str)					//If a new string is specified
		pointer = str;
	else if (!pointer)		//If called with null but no previous call specified a string
		return NULL;

	str = pointer + strspn(pointer, tokens);	//Advance str to the next token
	pointer = str + strcspn(str, tokens);		//Advance pointer to str so its set up for the next call
	
	pointer = *pointer ? *pointer = 0, pointer+1 : 0;	//If pointer doesnt equal to '\0' advance a position

	return str;
}