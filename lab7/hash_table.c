/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *     Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"


/*** Hash function. ***/

int hash(char *s)
{

}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value)
{

}


/* Free all the nodes of a linked list. */
void free_list(node *list)
{

}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table()
{

}


/* Free a hash table. */
void free_hash_table(hash_table *ht)
{

}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key)
{

}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value)
{

}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht)
{

}

