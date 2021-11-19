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

/* hash
 * 
 * Hashes a string into an integer mod some predefined value NSLOTS.
 * 
 * arguments: char *s: pointer to a char list (string)
 * return: int: an integer in the range [0, NSLOTS)
 */
int hash(char *s)
{
    int sum = 0;
    while (*s) {
        sum += (int) (*s);
        c++;
    }

    return sum % NSLOTS;
}


/*** Linked list utilities. ***/

/* create_node
 *
 * Create a single node with given key and value.
 *
 * arguments: char *key: string that acts as key identifier
 *            int value: value associated with node
 * return:  node *: returns the created node with key and value assigned.
 */
node *create_node(char *key, int value)
{
    node *ret;
    
    ret = (node *) malloc(sizeof(node));
    if (ret == NULL) {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }
    
    ret->key = key;
    ret->value = value;
    ret->next = NULL;

    return ret;
}


/* free_list
 * 
 * Free all the nodes of a linked list. 
 * 
 * arguments: node *list: pointer to the head of the linked list
 * return: void
 */
void free_list(node *list)
{
    node *temp;

    while (list != NULL) {
        temp = list;
        list = list->next;

        free(temp->key);
        free(temp);
    }
}


/*** Hash table utilities. ***/

/* create_hash_table
 *
 * Create a new hash table with array of pointers to heads of linked lists of 
 * nodes set initially to NULL.
 *
 * arguments: none
 * return: hash_table *: the created hash table
 *
 */
hash_table *create_hash_table()
{
    hash_table *ht;
    
    /* Allocate hash table */
    ht = (hash_table *)malloc(sizeof(hash_table));
    if (ht == NULL) {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }

    /* Allocate array of linked lists in hash table */
    /* Initialize all pointers to 0 = NULL. */
    ht->slots = (node **) calloc(NSLOTS, sizeof(node *));
    if (ht->slots == NULL) {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }

    return hash;
}


/* free_hash_table
 *
 * Free a hash table and its array of linked lists.
 *
 * arguments: hash_table *ht: pointer to hash table to free
 * return: void
 */
void free_hash_table(hash_table *ht)
{
    int i;

    if (ht != NULL) {
        /* Iterate through slots in hash table. */
        for(i = 0; i < NSLOTS; i++) {
            /* Each slot is a linked list. */
            free_list(ht->slots[i]);
        }
        
        free(ht->slots);
        free(ht);
    }
}


/* get_value
 *
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 *
 * arguments: hash_table *ht: hash table to get value from
 *            char *key: the key of the key/value pair
 * return: the value if it exists otherwise returns 0
 */
int get_value(hash_table *ht, char *key)
{
    node *curr;

    if (ht != NULL) {
        /* Iterate through the linked list. */
        curr = ht->slots[hash(key)];
        while (curr != NULL) {
            if (strcmp(key, curr->key) == 0) {
                return curr->value;
            }
            curr = curr->next;
        }
    }
    
    return 0;
}


/* set_value
 *
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 *
 * arguments: hash_table *ht: the hash table that holds the key/value pair
 *            char *key: the string identifier for the value.
 *            int value: the value to be set
 * 
 * return: void
 */
void set_value(hash_table *ht, char *key, int value)
{
    int hash_key;
    node *curr, *new_node;

    hash_key = hash(key);
    if (ht != NULL) {
        /* Iterate through the linked list. */
        curr = ht->slots[hash_key];
        while (curr != NULL) {
            if (strcmp(key, curr->key) == 0) {
                curr->value = value;
                free(key);
                return;
            }
            curr = curr->next;
        }

        new_node = create_node(key, value);
        new_node->next = ht->slots[hash_key];
        ht->slots[hash_key] = new_node;
    }

    /* If the pointer to the hash table doesn't exist, are probably still
     * expected to free the key because that is what is usually done. */
    free(key);
}


/* print_hash_table: 
 *
 * Print out the contents of the hash table as key/value pairs. 
 *
 * arguments: hash_table *ht: pointer to the hash table
 * return: void
 */
void print_hash_table(hash_table *ht)
{
    int i;
    node *curr;     /* Node to keep track of pointer in linked list. */

    /* Check if hash table exists. */
    if (ht != NULL) {
        /* Iterate through slots in the hash table. */
        for (i = 0; i < NSLOTS; i++) {
            curr = ht->slots[i];
            /* Iterate through the linked lists in each slot. */
            while (curr != NULL) {
                /* Print each key : value pair. */
                printf("%s %d", curr->key, curr->value);
                curr = curr->next;
            }
        }
    }
}

