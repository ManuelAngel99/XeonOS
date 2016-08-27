/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-25 11:16:21
* 
* File: buddy_tree.c
* Description:
*/


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <buddy_tree.h>

static void node_insert_key_and_right_subtree(buddy_tree_node_t* node, buddy_tree_key_t key, void* value, buddy_tree_node_t* right_subtree);
static void node_initialize(buddy_tree_node_t* node);
static void node_insert_key_and_left_subtree(buddy_tree_node_t* node, buddy_tree_key_t key, void* value, buddy_tree_node_t* left_subtree);
static size_t find_key_by_subtree(buddy_tree_node_t* node, buddy_tree_node_t* subtree, bool right_subtree);
static void node_remove_key_and_left_subtree(buddy_tree_node_t* node, buddy_tree_key_t key);
static void node_remove_key_and_right_subtree(buddy_tree_node_t* node, buddy_tree_key_t key);
static void node_initialize(buddy_tree_node_t* node);
static void node_insert_key_and_left_subtree(buddy_tree_node_t* node, buddy_tree_key_t key, void* value, buddy_tree_node_t* left_subtree);
static void rotate_from_left(buddy_tree_node_t* left_node, buddy_tree_node_t* right_node, size_t parent_index);
static void rotate_from_right(buddy_tree_node_t* left_node, buddy_tree_node_t* right_node, size_t parent_index);
static bool try_insery_by_rotating_to_left(buddy_tree_node_t* node, buddy_tree_key_t insert_key, void* insert_value, buddy_tree_node_t* right_subtree);
static bool try_insery_by_rotating_to_right(buddy_tree_node_t* node, buddy_tree_key_t insert_key, void* insert_value, buddy_tree_node_t* right_subtree);
static buddy_tree_node_t* node_split(buddy_tree_node_t* node, buddy_tree_key_t key, void* value, buddy_tree_node_t* right_subtree, buddy_tree_key_t* median);
static void _buddy_tree_insert(buddy_tree_t* tree, buddy_tree_node_t* node, buddy_tree_key_t insert_key, void* insert_value, buddy_tree_node_t* right_subtree);
static void _buddy_tree_remove(buddy_tree_t* tree, buddy_tree_node_t* container_node, buddy_tree_key_t key_to_remove);
static buddy_tree_node_t* node_combine(buddy_tree_node_t* node);
static bool try_rotation_from_right(buddy_tree_node_t *left_node);
static bool try_rotation_from_left(buddy_tree_node_t *right_node);
static void budddy_tree_destroy_subtree(buddy_tree_node_t* root_node);

void buddy_tree_create(buddy_tree_t* tree)
{
    circular_list_initialize(&tree->leaf_head);
    tree->root_node = (buddy_tree_node_t*) malloc(sizeof(buddy_tree_node_t));
    node_initialize(tree->root_node);
    circular_list_append(&tree->root_node->leaf_link, &tree->leaf_head);
}


buddy_tree_node_t* buddy_tree_leaf_left_neighbour(buddy_tree_t* tree, buddy_tree_node_t* node)
{
	assert(LEAF_NODE(node));
	if (node->leaf_link.prev != &tree->leaf_head)
		return list_get_instance(node->leaf_link.prev, buddy_tree_node_t, leaf_link);
	else
		return NULL;
}


buddy_tree_node_t* btree_leaf_node_right_neighbour(buddy_tree_t *tree, buddy_tree_node_t *node)
{
	assert(LEAF_NODE(node));
	if (node->leaf_link.next != &tree->leaf_head)
		return list_get_instance(node->leaf_link.next, buddy_tree_node_t, leaf_link);
	else
		return NULL;
}

//Insert key-value pair into the tree
void buddy_tree_insert_node(buddy_tree_t* tree, buddy_tree_node_t* leaf_node, buddy_tree_key_t insert_key, void* insert_value)
{
	buddy_tree_node_t* aux_node;

	assert(insert_value);

	aux_node = leaf_node;
	if(!aux_node)
		if(buddy_tree_search_key(tree, &aux_node, insert_key))
			printf("ERROR IN BUDDY TREE INSERT; THE TREE ALREADY HAS THAT KEY\n");

	_buddy_tree_insert(tree, aux_node, insert_key, insert_value, NULL);
}

//Remove a node from the buddy tree, it the leaf pointer is not null it will be a pointer to the leaf node where the key is present
void buddy_tree_delete_node(buddy_tree_t* tree, buddy_tree_node_t* leaf_node, buddy_tree_key_t key_to_remove)
{
	buddy_tree_node_t* aux_leaf_node;

	aux_leaf_node = leaf_node;
	if(!aux_leaf_node)
		if(!buddy_tree_search_key(tree, &aux_leaf_node, key_to_remove))
		{
			printf("\n\nERROR WHILE DELETING NODE\n\n");
			return;
		}
	
	_buddy_tree_remove(tree, aux_leaf_node, key_to_remove);
}

// Search a key in a buddy tree, the leaf_node** is the adress where the visited leaf node pointer will be put
void* buddy_tree_search_key(buddy_tree_t* tree, buddy_tree_node_t** leaf_node, buddy_tree_key_t key_to_search)
{
	buddy_tree_node_t *current, *next;
	
	//Go from the root to the leaf with the searched key
	for(current = tree->root_node; current; current = next)
	{
		*leaf_node = current;

		//The key couldn't be found
		if(current->keys == 0)
			return NULL;
		
		if(key_to_search < current->key[0])
		{
			next = current->subtree[0];
			continue;
		}
		else
		{
			void* value;
			size_t i;

			//The key is smaller than the current node [0] key so it must be in this subtree

			for(i = 1;  i < current->keys; i++)
			{
				if(key_to_search < current->key[i])
				{
					next = current->subtree[i];
					value = current->value[i -1];

					if(LEAF_NODE(current))
						return key_to_search == current->key[ i - 1] ? value : NULL;

					goto descend;
				}
			}

			//The key could also be in the right most subtree
			next = current->subtree[i];
			value = current->value[i - 1];

			if(LEAF_NODE(current))
				return key_to_search == current->key[ i - 1] ? value : NULL;
		}
descend:
		;
	}

	//Couldn't find the key in the *leaf_node and is smaller than any of its keys
	return NULL;
}


void buddy_tree_destroy(buddy_tree_t* tree)
{
	budddy_tree_destroy_subtree(tree->root_node);
}

//Recursive function that destroys every node below the specified root node
static void budddy_tree_destroy_subtree(buddy_tree_node_t* root_node)
{
    unsigned int index;
    
    if(root_node->keys)
        for(index = 0; index < root_node->keys + 1; index++)
            if(root_node->subtree[index])
                budddy_tree_destroy_subtree(root_node->subtree[index]);
    
    free(root_node);
}

static void node_insert_key_and_right_subtree(buddy_tree_node_t* node, buddy_tree_key_t key, void* value, buddy_tree_node_t* right_subtree)
{
	size_t i, j;

	// The keys are sorted from smaller to greater values 
	for(i = 0; i < node->keys; i++)
		if(key < node->key[i])
		{
			//Move the theys bigger than the provided key one position to the right
			for(j = node->keys; j > i; j--)
			{
				node->subtree[j + 1] = node->subtree[j];
				node->key[j] = node->key[j-1];
				node->value[j] = node->value[j-1];
			}
			break;
		}

	node->keys++;				//Now the tree has an extra key
	node->key[i] = key;
	node->value[i] = value;
	node->subtree[i + 1] = right_subtree;
}

static void node_initialize(buddy_tree_node_t* node)
{
    unsigned int index = 0;
    
    node->keys = 0;
    linked_list_initialie(&node->leaf_link);
    
    
    // Init every key and value to 0 (also the extra key)
    for(index = 0; index < BUDDY_TREE_MAX_KEYS + 1; index++)
    {
       node->key[index] = 0;
       node->value[index] = NULL;
       node->subtree[index] = NULL;
    }
    
    node->subtree[index] = NULL;
    node->parent = NULL;
    
}

static void node_insert_key_and_left_subtree(buddy_tree_node_t* node, buddy_tree_key_t key, void* value, buddy_tree_node_t* left_subtree)
{
	size_t i, j;

	// The keys are sorted from smaller to greater values 
	for(i = 0; i < node->keys; i++)
		if(key < node->key[i])
		{
			//Move the theys bigger than the provided key one position to the right
			for(j = node->keys; j > i; j--)
			{
				node->subtree[j + 1] = node->subtree[j];
				node->key[j] = node->key[j-1];
				node->value[j] = node->value[j-1];
			}
			node->subtree[j + 1] = node->subtree[j];
			break;
		}

	node->keys++;				//Now the tree has an extra key
	node->key[i] = key;
	node->value[i] = value;
	node->subtree[i] = left_subtree;
}

//Returns the index of a node with a given subtree
static size_t find_key_by_subtree(buddy_tree_node_t* node, buddy_tree_node_t* subtree, bool right_subtree)
{
	size_t i;

	for(i = 0; i < node->keys; i++)
		if(subtree == node->subtree[i])
			return i - (int) (right_subtree != false); //If we are looking for the right subtree substract 1 from the index

		printf("\nERROR, NODE %p DOESN'T CONTAIN SUBTREE %p",node, subtree );
		return 0;
}

//Removes a node and its left subtree
static void node_remove_key_and_left_subtree(buddy_tree_node_t* node, buddy_tree_key_t key)
{
	size_t i, j;

	//Search for the node to remove
	for(i = 0; i < node->keys; i++)
		if(key == node->key[i])
		{
			//Move the theys bigger than the provided key one position to the left
			for(j = i + 1; j < node->keys; j++)
			{
				node->key[j-1] = node->key[j];
				node->value[j-1] = node->value[j];
				node->subtree[j-1] = node->subtree[j];
			}
		node->subtree[ j - 1] = node->subtree[j];
		node->keys--;				//Now the tree has one key less
		return;
		}

	printf("\nERROR, NODE DOESN'T CONTAIN KEY\n\n" );
	return;
}

//Removes a node and its right subtree
static void node_remove_key_and_right_subtree(buddy_tree_node_t* node, buddy_tree_key_t key)
{
	size_t i, j;

	//Search for the node to remove
	for(i = 0; i < node->keys; i++)
		if(key == node->key[i])
		{
			//Move the theys bigger than the provided key one position to the left
			for(j = i + 1; j < node->keys; j++)
			{
				node->key[j-1] = node->key[j];
				node->value[j-1] = node->value[j];
				node->subtree[j] = node->subtree[j + 1];
			}
		node->keys--;				//Now the tree has one key less
		
		return;
		}

	printf("\nERROR, NODE DOESN'T CONTAIN KEY\n\n");
	return;
}

//Move the key-value-rsubtree with the biggest key from the left sibling to the right sibling
static void rotate_from_left(buddy_tree_node_t* left_node, buddy_tree_node_t* right_node, size_t parent_index)
{
	buddy_tree_key_t key = left_node->key[left_node->keys -1];	//Get the last key of the left tree

	if(LEAF_NODE(left_node))								//If this node is a leaf node
	{
		void* value = left_node->value[left_node->keys - 1];//Store the value of the leaf node

		node_remove_key_and_right_subtree(left_node, key);
		node_insert_key_and_left_subtree(right_node, key, value, NULL);
		left_node->parent->key[parent_index] = key;			//Update the parent key
	}
	else
	{
		buddy_tree_node_t* right_subtree = left_node->subtree[left_node->keys];		//Copy the last subtree
		
		node_remove_key_and_right_subtree(left_node, key);
		node_insert_key_and_left_subtree(right_node, left_node->parent->key[parent_index], NULL, right_subtree);
		left_node->parent->key[parent_index] = key;

		//Change the right_subtree parent to the right node
		right_subtree->parent = right_node;
	}
}

//Move the key-value-lsubtree with the smallest key from the right sibling to the left sibling
static void rotate_from_right(buddy_tree_node_t* left_node, buddy_tree_node_t* right_node, size_t parent_index)
{
	buddy_tree_key_t key = right_node->key[0];				//Get the first key of the right tree
	
	if(LEAF_NODE(right_node))								//If this node is a leaf node
	{
		void* value = right_node->value[0];						//Store the value of the leaf node

		node_remove_key_and_left_subtree(right_node, key);
		node_insert_key_and_right_subtree(left_node, key, value, NULL);
		right_node->parent->key[parent_index] = right_node->key[0];			//Update the parent key
	}
	else
	{
		buddy_tree_node_t* left_subtree = right_node->subtree[0];		//Copy the first subtree
		
		node_remove_key_and_left_subtree(right_node, key);
		node_insert_key_and_right_subtree(left_node, right_node->parent->key[parent_index], NULL, left_subtree);
		right_node->parent->key[parent_index] = key;

		//Change the left_subtree parent to the left node
		left_subtree->parent = right_node;
	}
}

// Insert a key-value-rsubtree and rotate the left-most node to the left
static bool try_insery_by_rotating_to_left(buddy_tree_node_t* node, buddy_tree_key_t insert_key, void* insert_value, buddy_tree_node_t* right_subtree)
{
	size_t index;
	buddy_tree_node_t * left_node;

	if(ROOT_NODE(node))													//This operation cannot be performed on a root node
		return false;

	index = find_key_by_subtree(node->parent, node, true);
	if((int)index == -1)												//This is the node that is at the left of his parent and the rotation is impossible
		return false;

	left_node = node->parent->subtree[index];							//Get the left node
	if(left_node->keys < BUDDY_TREE_MAX_KEYS)							//If it has enough space the rotation can be made
	{
		node_insert_key_and_right_subtree(node, insert_key, insert_value, right_subtree);
		rotate_from_right(left_node, node, index);
		return true;
	}

	return false;
}

// Insert a key-value-subtree and rotate the right-most node to the right
static bool try_insery_by_rotating_to_right(buddy_tree_node_t* node, buddy_tree_key_t insert_key, void* insert_value, buddy_tree_node_t* right_subtree)
{
	size_t index;
	buddy_tree_node_t * right_node;

	if(ROOT_NODE(node)) //This operation cannot be performed on a root node
		return false;

	index = find_key_by_subtree(node->parent, node, false);
	if(index == node->parent->keys)												//This is the node that is at the right of his parent and the rotation is impossible
		return false;

	right_node = node->parent->subtree[index + 1];						//Get the left node
	if(right_node->keys < BUDDY_TREE_MAX_KEYS)							//If it has enough space the rotation can be made
	{
		node_insert_key_and_left_subtree(node, insert_key, insert_value, right_subtree);
		rotate_from_left(node, right_node, index);
		return true;
	}

	return false;
}

/*
*  This function splits a node form the tree and returns a pointer to the new node containing the keys greater
*  or equal than the median of the old keys and the key provided and store the median key to the specified
*  memory adress
*/
static buddy_tree_node_t* node_split(buddy_tree_node_t* node, buddy_tree_key_t key, void* value,
									 buddy_tree_node_t* right_subtree, buddy_tree_key_t* median)
{
	buddy_tree_node_t* right_node;
	size_t i, j;

	assert(median);
	assert(node->keys == BUDDY_TREE_MAX_KEYS);

	//Use the extra space in the key array to store the extra node
	node_insert_key_and_right_subtree(node, key, value, right_subtree);
	//Get the median of the keys
	*median = MIDDLE_NODE(node);

	//Allocate and initialize the node
	right_node = (buddy_tree_node_t*)malloc(sizeof(buddy_tree_node_t));
	node_initialize(right_node);
	right_node->parent = node->parent;


	i = (size_t)INDEX_NODE(node);
    for (i += MIDDLE_NODE_INDEX(node), j = 0; i < node->keys; i++, j++)
	{
		right_node->key[j] = node->key[i];
		right_node->value[j] = node->value[i];
		right_node->subtree[j] = node->subtree[i];

		//Fix the parent link in the subtree
		if(right_node->subtree[j])
			right_node->subtree[j]->parent = right_node;
	}

	right_node->subtree[j] = node->subtree[i];
	if(right_node->subtree[j])
		right_node->subtree[j]->parent = right_node;

	//Update the number of keys in each node;
	right_node->keys = j;
	node->keys /= 2;

	return right_node;
}


/*
* Recusrevily insert elements into a buddy tree:
* Starts inserting the right subtree-key-value into the specified node 
*/
static void _buddy_tree_insert(buddy_tree_t* tree, buddy_tree_node_t* node, buddy_tree_key_t insert_key,
			void* insert_value, buddy_tree_node_t* right_subtree)
{
	if (node->keys < BUDDY_TREE_MAX_KEYS)
		node_insert_key_and_right_subtree(node, insert_key, insert_value, right_subtree);		//Node has space to insert the new node
	else if(try_insery_by_rotating_to_left(node, insert_key, insert_value, right_subtree))
    {
        //The node has been inserted by moving some keys to the left sibling
    }
	else if(try_insery_by_rotating_to_right(node, insert_key, insert_value, right_subtree))
	{
		//The node has been inserted by mobving some keys to the right sibling
    }
    else
	{
		buddy_tree_node_t* right_node;
		buddy_tree_key_t median_key;

		right_node = node_split(node, insert_key, insert_value, right_subtree, &median_key);

		/*
		* The node and its two siblings are full, split the node and insert the new node into its parent
		*/

		if(LEAF_NODE(node))
			circular_list_prepend(&right_node->leaf_link, &node->leaf_link);
		if(ROOT_NODE(node))
		{
			//The root node was splited, so a new tree will be created
			tree->root_node = (buddy_tree_node_t*) malloc(sizeof(buddy_tree_node_t));
			node->parent = tree->root_node;
			right_node->parent = tree->root_node;
			node_initialize(tree->root_node);

			// The left subtree will be the old root and the right hand will be the right node
			tree->root_node->subtree[0] = node;
		}
		_buddy_tree_insert(tree, node->parent, median_key, NULL, right_node);
	}
}

//Rotate a key from the left sibling ot from the index node if it is possible
static bool try_rotation_from_left(buddy_tree_node_t *right_node)
{
	size_t index;
	buddy_tree_node_t* left_node;

	//A rotation cannot be performed if this is a root node
	if(ROOT_NODE(right_node))
		return false;

	//If this is the left most subtree the rotation can't be made
	index = find_key_by_subtree(right_node->parent, right_node, true);
	if((int)index == -1)
		return false;

	left_node = right_node->parent->subtree[index];
	if(left_node->keys > FILL_FACTOR)
	{
		rotate_from_left(left_node, right_node, index);
		return true;
	}

	return false;
}

static bool try_rotation_from_right(buddy_tree_node_t *left_node)
{
	size_t index;
	buddy_tree_node_t* right_node;

	//A rotation cannot be performed if this is a root node
	if(ROOT_NODE(left_node))
		return false;

	//If this is the right most subtree the rotation can't be made
	index = find_key_by_subtree(left_node->parent, left_node, false);
	if(index == left_node->parent->keys)
		return false;

	right_node = left_node->parent->subtree[index +1];
	if(right_node->keys > FILL_FACTOR)
	{
		rotate_from_right(left_node, right_node, index);
		return true;
	}

	return false;
}

//Combine a node with its siblings
static buddy_tree_node_t* node_combine(buddy_tree_node_t* node)
{
	size_t index, i;
	buddy_tree_node_t* right_node;

	assert(!ROOT_NODE(node));

	index = find_key_by_subtree(node->parent, node, false);
	if(index == node->parent->keys)
	{
		//This is the right most node of the tree
		index--;
		right_node = node;
		node = node->parent->subtree[index + 1];
	}
	else
		right_node = node->parent->subtree[index + 1];

	// Index nodes need to insert parent node key in between left and right node
	if(INDEX_NODE(node))
		node->key[node->keys++] = node->parent->key[index];

	// Copy the key, its value and its subtree
	for(i = 0; i < right_node->keys; i++)
	{
		node->key[node->keys + i] = right_node->key[i];
		node->value[node->keys + i] = right_node->value[i];

		if(INDEX_NODE(node))	//If this is an index node we will also copy its the subtree and adjust the parent of that subtree
		{
			node->subtree[node->keys + i] = right_node->subtree[i];
			right_node->subtree[i]->parent = node;					
		}

	}

	node->keys += right_node->keys;
	return node;
}


//Recursive delete a key from a node
static void _buddy_tree_remove(buddy_tree_t* tree, buddy_tree_node_t* container_node, buddy_tree_key_t key_to_remove)
{
	if(ROOT_NODE(container_node))
	{
		if ((container_node->keys == 1 ) && (container_node->subtree[0]))
		{
			// Set a new root and crreate a new one
			tree->root_node = container_node->subtree[0];
			tree->root_node->parent = NULL;
			free(container_node);
		}
		else
			//Remove the key from the root node
			node_remove_key_and_right_subtree(container_node, key_to_remove);
		
		return;
	}

	if(container_node->keys <= FILL_FACTOR)
	//If the node is below the fill factor try to get some keys from the left or the right siblings
		if(!try_rotation_from_left(container_node))
			try_rotation_from_right(container_node);
	
	if(container_node->keys > FILL_FACTOR)
	{
		// The key can be removed, the right subtree is removed because when containing two nodes the left sibling is preserved and the right is freed
		node_remove_key_and_right_subtree(container_node, key_to_remove);
		for (size_t i = 0; i < container_node->keys; i++)
			if(container_node->parent->key[i] == key_to_remove)
				container_node->parent->key[i] = container_node->key[0];
	
	}
	else
	{
		// The node and its two siblings are below the fill factor so the node will be combined with one of its siblings
		size_t index;
		buddy_tree_node_t* right_node;
		buddy_tree_node_t* parent;

		parent = container_node->parent;
		node_remove_key_and_right_subtree(container_node, key_to_remove);
		right_node = node_combine(container_node);

		if(LEAF_NODE(right_node))
			circular_list_remove(&right_node->leaf_link);
			
		index = find_key_by_subtree(parent, right_node , true);
		assert((int) index != -1);
		
		//Free the right sibling wich has been combined
		free(right_node);
		_buddy_tree_remove(tree, parent, parent->key[index]);
	}

}