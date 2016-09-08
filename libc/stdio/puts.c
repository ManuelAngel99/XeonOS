/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-08 12:59:40 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-08 13:28:54
 * 
 * Description: The puts function prints a string to the tty
 */

 #include <stdio.h>

int	puts(const char* string)
{
    return fputs(string, stdout);
}