/* 
 * Donovan Ye
 * CS 11: C Track Lab 6
 *
 * The following program, quicksorter, behaves as follows:
 *
 *      Sorts an arbitrary number of integers inputed on the command line, 
 *          printing the sorted numbers in ascending order, one per line.
 *      If there are no command line arguments at all , the program should
 *          prints out a usage message. 
 *      The program uses the quicksort algorithm and utilizes linked lists
 *      If the optional command line argument -q is found anywhere in the 
 *          command line, output of the program is suppressed.
 *      If any of the command line arguments to the program are not integers
 *          or one of the two optional command line arguments, the program's
 *          response is undefined i.e. it can do anything. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "memcheck.h"
#include "linked_list.h"

/* Returns a sorted linked list copy of inputed pointer head */
node *quicksort(node *list);

/*
 * quicksort: sorts a linked list of integers in ascending order using the 
 *              quicksort algorithm
 * argument: node *list: pointer to the head of a linked list to be sorted
 * return: node *: pionter to head of the sorted list
 */
node *quicksort(node *list) {
    node *pivot,    /* copy of the first node to act as a pivot */
    *curr,          /* pointer to node for scanning */
    *high,          /* pointer to list of values greater than the pivot */ 
    *low,           /* pointer to list of values less than the pivot */
    *sorted_high,   /* pointer to sorted values greater than the pivot */
    *sorted_low,    /* pointer to sorted values less than the pivot */
    *sorted;        /* pointer to sorted list to return */

    /* If list has zero nodes or one node, copy the list as-is and return. */
    if (!list || list->next == NULL) {
        return copy_list(list);
    }

    pivot = list;       /* Create a copy of the first node */

    /* Create two new lists from the rest of the original list 
     * Iterate through linked list and add copy of the current node to 
     * high or low depending on if its greater than or less than the pivot. 
     */ 
    curr = list->next;
    high = NULL;
    low = NULL;
    while (curr != NULL) {
        if (curr->data > pivot->data) {
            /* Greater than */
            high = create_node(curr->data, high);
        } else {
            /* Less than or equal to */
            low = create_node(curr->data, low);
        }
        curr = curr->next;
    }   

    /* Sort these two new lists using a recursive call to quicksort. */
    sorted_high = quicksort(high);
    sorted_low = quicksort(low); 

    /* Append everything together in order */
    sorted_high = create_node(pivot->data, sorted_high);
    sorted = append_lists(sorted_low, sorted_high);

    /* Free allocated memory. */
    free_list(high);
    free_list(low);
    free_list(sorted_high);
    free_list(sorted_low);

    assert(is_sorted(sorted));      /* Check that the list is sorted. */

    return sorted;
}
      

int main(int argc, const char* argv[]) {
    int i;
    int q_arg;      /* flag for quiet mode */
    node *list;     /* inputed list */
    node *sorted;   /* sorted copy of inputed list */

    q_arg = 0;
    list = NULL;

    /* Iterate through each command-line argument except the first */
    for (i = 1; i < argc; i++) {
        /* Check for output suppression argument */
        if (strcmp(argv[i], "-q") == 0) {
            q_arg = 1;
        } else {
            /* add node to head of list */
            list = create_node(atoi(argv[i]), list);
        }
    }

    /* usage message if the list has no elements */
    if (list == NULL) {
        fprintf(stderr, "usage: %s [-q] number1 [number2 ...]\n", argv[0]);
        exit(1);
    }

    sorted = quicksort(list);   /* Sort the linked list. */

    /* Print list if not suppressed. */
    if (!q_arg) {
        print_list(sorted);
    }

    /* Free allocated memory. */
    free_list(list);
    free_list(sorted);
    
    print_memory_leaks();   /* Check for memory leaks. */

    return 0;
}