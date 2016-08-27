#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>
#include <sys/cdefs.h>

#ifdef _cplusplus
	extern "C" {
#endif


//For staticall lists
#define CREATE_LINKED_LIST( name ) \
    link_t name = {.prev = &name, .next = &name}
    
typedef struct link
{
    struct link* prev;
    struct link* next;
}link_t;

//For double linked lists
static inline void linked_list_initialie(link_t* link)
{
    link->prev = NULL;
    link->next = NULL;
}

//For circular linked lists
static inline void circular_list_initialize(link_t *head)
{
    head->prev = head;
    head->next = head;
}

// Add a link to the beggining of a circular linked list
static inline void circular_list_prepend(link_t* link, link_t* head)
{
    link->next = head->next;
    link->prev = head;
    head->next->prev = link;
    head->next = link;
}

// Add a link to the end of a circular linked list
static inline void circular_list_append(link_t* link, link_t* head)
{
    link->prev = head->prev;
    link->next = head;
    head->prev->next = link;
    head->prev = link;
}

//Remove an item from a circular linked list
static inline void circular_list_remove(link_t* link)
{
    link->next->prev = link->prev;
    link->prev->next = link->next;
    linked_list_initialie(link);                    //The link will now be NULL
}

//Retruns true if the list is empty or false if it isn't
static inline bool circular_list_empty(link_t* head)
{
    return head->next == head ? true : false;
}

//Concatenates two separated lists or splits them if they were alreday concatenated
static inline void circular_list_split_or_concat(link_t* first_head, link_t* second_head)
{
    first_head->prev->next = second_head;
    second_head->prev->next = first_head;
    link_t* helper = first_head->prev;
    first_head->prev = second_head->prev;
    second_head->prev = helper;
}

//Split a circular list in two separate circular lists
static inline void circular_list_split(link_t* first_head, link_t* second_head)
{
    circular_list_split_or_concat(first_head, second_head);
}

//Concatenate two separate circular lists
static inline void circular_list_concat(link_t* first_head, link_t* second_head)
{
    circular_list_split_or_concat(first_head, second_head);
}

#define list_get_instance(link, type, member) \
	((type *)(((uint8_t *)(link)) - ((uint8_t *)&(((type *)NULL)->member))))

bool list_member(link_t* link, link_t* list);
void list_concat(link_t* first_head, link_t* second_head);

#ifdef _cplusplus
	}
#endif


#endif
