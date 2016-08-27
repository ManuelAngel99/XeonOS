/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-25 10:53:15
* 
* File: list_member.c
* Description: A function that tests if a a link belong to a determinated list
*/

#include <linked_list.h>
#include <stdbool.h>

bool list_member(link_t* link, link_t* list)
{
    link_t* iterator = list->next;
    while(iterator != list)
    {
        if(iterator->next == link)
            return true;
        
        iterator = iterator->next;
    }
    return false;
}