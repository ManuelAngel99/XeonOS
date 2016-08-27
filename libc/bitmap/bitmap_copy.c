/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-25 10:34:00
* 
* File: bitmap_copy.c
* Description: A function that copies count bits from a bitmap to another
*/
#include <bitmap.h>
#include <assert.h>

void bitmap_copy(bitmap_t* source, bitmap_t* destination, size_t count)
{
    assert(count <= destination->elements_count);
    assert(count <= source->elements_count);
    
    //Copy a dword at a time
    size_t i;
    for(i = 0; i< count / BITMAP_UNITS; i++)
    {
        destination->content[i] = source->content[i];
    }
    
    if(count % BITMAP_UNITS)
    {
        bitmap_clear_range(destination, i * BITMAP_UNITS, count % BITMAP_UNITS);
        destination->content[i] |= source->content[i] & ((1 <<  (count % BITMAP_UNITS) ) - 1);
    }
}