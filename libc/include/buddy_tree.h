#ifndef _BUDDY_TREE_H
#define _BUDDY_TREE_H

#include <linked_list.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/cdefs.h>

#ifdef _cplusplus
	extern "C" {
#endif


#define BUDDY_TREE_M 5
#define BUDDY_TREE_MAX_KEYS (BUDDY_TREE_M - 1)

#define LEAF_NODE(node)     ((node)->subtree[0] == NULL)
#define INDEX_NODE(node)    ((node)->subtree[0] != NULL)
#define ROOT_NODE(node)     (!(node)->parent)
#define FILL_FACTOR         ((BUDDY_TREE_M - 1) / 2)

#define MIDDLE_NODE_INDEX(node) ((node)->keys / 2)
#define MIDDLE_NODE(node)   ((node)->key[MIDDLE_NODE_INDEX(node)])


typedef uint64_t buddy_tree_key_t;

typedef struct buddy_tree_node
{
    size_t keys;                                        // Number of keys
    buddy_tree_key_t key[BUDDY_TREE_MAX_KEYS +1];           // Only single keys are supported
    void *value[BUDDY_TREE_MAX_KEYS + 1];               // Pointer to the values sorted according to the key array
    struct buddy_tree_node* subtree[BUDDY_TREE_M + 1];  // Pointer to the childern of this node sorted by the key array
    struct buddy_tree_node* parent;                     // Pointer to the parent of this node
    
    link_t leaf_link;                                   // Link connecting leaf-level nodes (this is not defined to the root node)
    link_t bfs_link;
    int depth;
}buddy_tree_node_t;

typedef struct budddy_tree
{
    link_t leaf_head;                                   //List of all the leaves
    buddy_tree_node_t *root_node;
}buddy_tree_t;

void buddy_tree_create(buddy_tree_t*);
void buddy_tree_destroy(buddy_tree_t*);

void buddy_tree_insert_node(buddy_tree_t*, buddy_tree_node_t*, buddy_tree_key_t, void*);
void buddy_tree_delete_node(buddy_tree_t*, buddy_tree_node_t*, buddy_tree_key_t);
void*buddy_tree_search_key(buddy_tree_t*, buddy_tree_node_t**, buddy_tree_key_t); 

buddy_tree_node_t* buddy_tree_leaf_left_neighbour(buddy_tree_t*, buddy_tree_node_t*);
buddy_tree_node_t* buddy_tree_leaf_right_neighbour(buddy_tree_t*, buddy_tree_node_t*);


#ifdef _cplusplus
	}
#endif


#endif
