/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-25 10:31:20
* 
* File: bitmap_clear_range.c
* Description: Clears n bits of a bitmap starting from the specified pos
*/
#include <bitmap.h>
#include <assert.h>
#include <align.h>
#include <macros.h>

void bitmap_clear_range(bitmap_t* bitmap, size_t starting_pos, size_t count)
{
    assert(starting_pos + count <= bitmap->elements_count);
    
    if(count == 0)
        return;
    
    //We set the range it three steps, first, the lower unaligned bits, then the middle and to finish set the top unaligned
    size_t starting_page = starting_pos / BITMAP_UNITS;
    size_t aligned_start =  ALIGN_UP(starting_pos, BITMAP_UNITS);
    
    size_t leading_unaligned_bits = min( aligned_start - starting_pos, count);
    size_t aligned_bits = (count > leading_unaligned_bits? count - leading_unaligned_bits : 0);
    size_t trailing_unaligned_bits = aligned_bits % BITMAP_UNITS;
    
    if(starting_pos + count < aligned_start) //If there are only unaligned bits
    {
        bitmap->content[starting_page] &= ~((1 << leading_unaligned_bits) -1) << (starting_pos & BITMAP_REMAINER);
        return;
    }
    
    if(leading_unaligned_bits) //Set the leading unaligned bits
    {
         bitmap->content[starting_page] &= ((1 << (BITMAP_UNITS - leading_unaligned_bits)) -1);
    }
    
    size_t i;
    for(i = 0; i < aligned_bits / BITMAP_UNITS; i++) //Set the middle bits a dword at a time
    {
        bitmap->content[aligned_start/BITMAP_UNITS + i] = BITMAP_EMPTY_PAGE;
    }
    
    if(trailing_unaligned_bits)
    {
        bitmap->content[aligned_start/BITMAP_UNITS + i] &= ~(1 << trailing_unaligned_bits) -1;
    }
    
    bitmap->next_fit = starting_page;
}
