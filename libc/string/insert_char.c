/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-08 11:00:52 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-08 11:01:54
 * 
 * Description: This function inserts a char at a specific position of a string
 */

#include <string.h>

char* insert_char(char* buffer, const size_t buffer_size, const char insert_char, const int pos)
{
	memmove(buffer + pos + 1, buffer + pos, buffer_size - (pos + 1));
	buffer[pos] = insert_char;
	return buffer;
}
