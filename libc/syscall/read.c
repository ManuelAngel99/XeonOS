/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-01 13:04:17 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-01 13:19:26
 * 
 * Description: 
 */

#include <stdio.h>
#include <syscall.h>
#include <stddef.h>

#if defined (__is_xeonos_kernel)
#include <devices/keyboard.h>
#endif

size_t read(int file_descriptor, void* buffer, size_t number)
{
    if( file_descriptor < 0 || number == 0 || buffer == NULL)
        return 0;
#if defined (__is_xeonos_kernel)
    if(file_descriptor == 0)
    {
        char* key;
        key = buffer;
        *key = keyboard_getch();
        return (char)*key;
    }
#else
#endif

    return -1;
}
