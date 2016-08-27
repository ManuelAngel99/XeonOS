/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-25 10:24:08
* 
* File: bitmap_size.c
* Description: The bitmap size function returns the number of pages that a bitmap with n elements will have
*/
#include <bitmap.h>

size_t bitmap_size(size_t element_count)
{
    return ( element_count % BITMAP_UNITS == 0 ? element_count / BITMAP_UNITS: element_count/BITMAP_UNITS + 1 );
}