/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-25 10:26:24
* 
* File: bitmap_allocate_range.c
* This function finds a continuous zero bit range in the bitmap
 * is also satisty a constraint(bits set in the constraint can't
 * be set in the adress)
 * 
 * @param bitmap       Bitmap to search in
 * @param count        Number of 0s
 * @param base         Starting adress of the bitmap
 * @param prefered     Prefered adress to start the search
 * @param constraint   Constraint for THE ADRESS
 * @param index        If NULL the bitmap isn't modified, if not the index is returned through this parameter and the bits are set
 */

#include <bitmap.h>

static inline bool bitmap_get_bit_fast(bitmap_t* bitmap, size_t element_number)
{
    return ( bitmap->content[element_number / BITMAP_UNITS] & ( 1 << (element_number & BITMAP_REMAINER)) );
}
static inline bool constraint_satisfy(size_t index, size_t base, size_t constraint)
{
    return (((base + index) & constraint) == 0);
}

bool bitmap_allocate_range(bitmap_t* bitmap, size_t count, size_t base, size_t prefered, size_t constraint, size_t* index)
{
    if(count == 0)
        return false;
    
    size_t size = bitmap_size(bitmap->elements_count);
    size_t next_fit = bitmap->next_fit;
    
    if( (prefered > base) && (prefered < base + bitmap->elements_count) )
    {
        size_t prefered_fit_page = (prefered-base) / BITMAP_UNITS;
        
        if(prefered_fit_page > next_fit)
            next_fit = prefered_fit_page;
    }
    
    for(size_t i = 0; i < size; i++)
    {
        size_t page = (next_fit + i) % size;
    
        if(bitmap->content[page] == BITMAP_FULL_PAGE) //Skip the current page if its full
            continue;
            
        for(size_t bit = 0; bit < BITMAP_UNITS; bit++) //Search bit by bit
        {
            size_t j = page * BITMAP_UNITS + bit;
            
            if( j >= bitmap->elements_count)
                break;
            if( !constraint_satisfy(j, base, constraint) ) //If the current index doesn't satisfy the constraint skip the current iteration
                continue;
            
            if(!bitmap_get_bit_fast(bitmap, j))
            {
                size_t continuous_bits = 1;                //Count how many continuous bits are found after i
                
                for(size_t k = 1; k < count; k++)
                {
                    if( (i + k < bitmap->elements_count)  && !bitmap_get_bit_fast(bitmap, j + k))
                        continuous_bits++;
                    else
                        break;
                }
                
                if(continuous_bits == count)
                {
                    if(index != NULL)
                    {
                        bitmap_set_range(bitmap, j, count);
                        bitmap->next_fit = i / BITMAP_UNITS;
                        *index = j;
                    }
                    
                    return true;
                }
                else
                    i+=continuous_bits;
            }
                
        }
    }
    return false;
}