/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-08 10:45:14 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-08 10:47:49
 * 
 * Description: A function that makes a string uppercase
 */

#include <string.h>
#include <ctype.h>

void string_to_upper(char* string)
{
	while(*string)
	{
		*string = toupper((unsigned char)*string);
		string++;
	}
}