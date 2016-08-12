/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 21:25:23
* 
* File: reverse.c
* Description:
*//*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 21:25:23
* 
* File: reverse.c
* Description: Implements the reverse function wich reverses a steing or a chunk of data
*/

#include <string.h>

char* reverse(char* str, const size_t length)
{
    size_t start = 0;
    size_t end = length -1;
    while (start < end)
    {
    	char temp = *(str+start);
    	*(str+start) = *(str+end);
    	*(str+end) = temp;

        start++;
        end--;
    }
    return str;
}