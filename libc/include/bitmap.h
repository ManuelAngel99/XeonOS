#ifndef BITMAP_H_INCLUDED
#define BITMAP_H_INCLUDED

#include <sys/cdefs.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef _cplusplus
	extern "C" {
#endif

//Defines the number of bits that a single unit can store, in this case it is 32 because we use uint32_t
#define BITMAP_UNITS 32
#define BITMAP_REMAINER 31

#define BITMAP_EMPTY_PAGE 0
#define BITMAP_FULL_PAGE 0xfffffff

typedef struct bitmap
{
    uint32_t* content;
    size_t elements_count;
    size_t next_fit;
}bitmap_t;


static inline void bitmap_set_bit(bitmap_t* bitmap, size_t element_number, bool value)
{
    if(element_number >= bitmap->elements_count)
        return;
    
    size_t content_page = element_number / BITMAP_UNITS;
    
    if(value == true)
        bitmap->content[content_page] |= (1 << (element_number & BITMAP_REMAINER)); 
    else
    {
        bitmap->content[content_page] &= ~(1 << (element_number & BITMAP_REMAINER));
        bitmap->next_fit = content_page;
    }
}

static inline bool bitmap_get_bit(bitmap_t* bitmap, size_t element_number)
{
    if(element_number >= bitmap->elements_count)
        return false;
    size_t content_page = element_number / BITMAP_UNITS;
    return ( bitmap->content[content_page] & ( 1 << (element_number & BITMAP_REMAINER)) );
}

size_t bitmap_size(size_t);
void bitmap_init(bitmap_t*, size_t, void *);
void bitmap_set_range(bitmap_t*, size_t, size_t);
void bitmap_clear_range(bitmap_t*, size_t, size_t);

bool bitmap_allocate_range(bitmap_t*, size_t, size_t, size_t, size_t, size_t *);
void bitmap_copy(bitmap_t*, bitmap_t*, size_t);

void bitmap_print_page(bitmap_t*, size_t);

#ifdef _cplusplus
}
#endif

#endif
