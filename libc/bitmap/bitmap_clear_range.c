/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-25 10:31:20
* 
* File: bitmap_clear_range.c
* Description: Clears n content of a bitmap starting from the specified pos
*/
#include <bitmap.h>
#include <assert.h>
#include <align.h>
#include <macros.h>

void bitmap_clear_range(bitmap_t* bitmap, size_t start, size_t lenght)
{
    assert(start + lenght <= bitmap->elements_count);
    
    if (lenght == 0)
        return;
    
    size_t first_page = start / BITMAP_UNITS;
    size_t aligned_start = ALIGN_UP(start, BITMAP_UNITS);
    

    /*
    * The delete will be split in three parts, first clear the first bits in the middle of a page(if any),
    * then delete the full pages and finally clear the bits in the beginning of the last page (if any)
    */
    size_t leading_unaligned_bits = min(aligned_start - start, lenght);
    size_t middle_bits = (lenght > leading_unaligned_bits) ? (lenght - leading_unaligned_bits) : 0;
    size_t trailing_aligned_bits = middle_bits  % BITMAP_UNITS;
    
    //If there are only leading unaligned bits clear them and return
    if (start + lenght < aligned_start)
    {
        bitmap->content[first_page] &= ~(((1 << leading_unaligned_bits) - 1) << (start & BITMAP_REMAINER));
        return;
    }
    //Clean the middle pages one at a time
    if (leading_unaligned_bits)
        bitmap->content[first_page] &= (1 << (BITMAP_UNITS - leading_unaligned_bits)) - 1;
    
    size_t i;
    for (i = 0; i < middle_bits  / BITMAP_UNITS; i++)
        bitmap->content[aligned_start / BITMAP_UNITS + i] = BITMAP_EMPTY_PAGE;

    //If there are trailing aligned bits clear rhem
    if (trailing_aligned_bits)
        bitmap->content[aligned_start / BITMAP_UNITS + i] &= ~((1 << trailing_aligned_bits) - 1);
    
    bitmap->next_fit = first_page;
}
