/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-08 13:08:08 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-08 13:26:14
 * 
 * Description: 
 */

#include <stdio.h>
#include <syscall.h>

int	putchar(int character)
{
    return fwrite((char*)&character, 1, 1, stdout);
}