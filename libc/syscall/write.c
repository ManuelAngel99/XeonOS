/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-01 13:04:17 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-08 15:03:35
 * 
 * Description: System call to write to a file descriptor
 */

#include <stdio.h>
#include <syscall.h>
#include <stddef.h>

#if defined (__is_xeonos_kernel)
#include <kernel/tty.h>
#endif

size_t write(int file_descriptor, void* buffer, size_t number)
{
    if( file_descriptor < 0 || number == 0 || buffer == NULL)
        return 0;
#if defined (__is_xeonos_kernel)
    if(file_descriptor == 1)
    {
        terminal_write((char*)buffer, number);
        return number;
    }
#else
#endif

    return -1;
}
