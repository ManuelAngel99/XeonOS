/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-25 10:29:19
* 
* File: bitmap_initialize.c
* Description: This function inits a bitmap with n elements to the data contained in the adress specified
* (where the bitmap will be stored)
*/
#include <bitmap.h>

void bitmap_initialize(bitmap_t* bitmap, size_t number_of_elements, void *address)
{
    bitmap->elements_count = number_of_elements;
    bitmap->content = (uint32_t*)address;
    bitmap->next_fit = 0;
}
