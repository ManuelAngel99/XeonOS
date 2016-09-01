/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-08-30 17:41:58 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-08-30 21:10:36
 *
 * Description: Defines the input output buffers table, the first three iob are stdin stdout and stderr
 */

#include <stdio.h>

#ifndef OPEN_MAX
#define OPEN_MAX 32
#endif

FILE __input_output_buffers[OPEN_MAX] =
{
    {0, 1, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0},
    {2, 1, 0, 0, 0, 0, 0, 0},
};