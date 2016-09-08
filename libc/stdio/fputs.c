/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-08 13:20:37 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-08 13:24:01
 * 
 * Description: Implementation of the fprints function that prints a data stream to a file stream
 */

#include <stdio.h>
#include <string.h>

int fputs(const char* string, FILE* stream)
{
    return fwrite(string, strlen(string), 1, stream);
}