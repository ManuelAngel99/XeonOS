/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-25 10:54:53
* 
* File: list_concat.c
* Description: A function that concatenates two lists and makes the second one NULL
*/
#include <linked_list.h>


void list_concat(link_t* first_head, link_t* second_head)
{
    if(circular_list_empty(second_head))
        return;
        
    second_head->next->prev = first_head->prev;
    second_head->prev->next = first_head;
    
    first_head->prev->next = second_head->next;
    first_head->prev = second_head->prev;
    
    linked_list_initialie(second_head);
}