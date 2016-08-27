/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-25 10:22:45
* 
* File: bitmap_print_page.c
* Description: Defines the print page function that prints the values contained in a bitmap page(32 bits)
*/

#include <bitmap.h>
#include <stdio.h>
#include <assert.h>

void bitmap_print_page(bitmap_t* bitmap, size_t page)
{
    assert(page < (bitmap->elements_count / BITMAP_UNITS) );
    
    if(page >= (bitmap->elements_count / BITMAP_UNITS) )
        return;
        
    for(size_t i = 0; i < BITMAP_UNITS; i ++ )
    {
        printf("%d",bitmap_get_bit( bitmap, page * BITMAP_UNITS + i));
    }
}