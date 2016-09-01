/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-01 12:46:10 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-01 13:12:48
 * 
 * Description: 
 */

#include <stdio.h>
#include <syscall.h>

int fgetc(FILE* file)
{
    unsigned char charcater;
    
    if( file->unget & (1 << 15) )
    {
        file->unget &= ~(1 << 15);
        return (int)file->unget;
    }

    if( read(file->file_descriptor, &charcater, 1) <= 0 )
        return EOF;

    return charcater;
}