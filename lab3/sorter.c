/* 
 * Donovan Ye
 * CS 11: C Track Lab 3
 *
 * The following program, sorter, behaves as follows:
 *
 *      Sorts a list of up to 32 integers inputed on the command line, 
 *          printing the sorted numbers in ascending order, one per line.
 *
 *      If there are no command line arguments at all , the program should
 *          prints out a usage message. 
 *      If there are more than 32 numbers on the command line, or no numbers
 *          at all, the program prints out the usage message and exits.
 *      By default, the program uses the minimum element sort algorithm.
 *      If the optional command line arguments -b is found anywhere in the 
 *          command line, the program uses the bubble sort algorithm instead.
 *      If the optional command line argument -q is found anywhere in the 
 *          command line, output of the program is suppressed.
 *      If any of the command line arguments to the program are not integers
 *          or one of the two optional command line arguments, the program's
 *          response is undefined i.e. it can do anything. 
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N 32    /* Maximum number of integers that we allow to be sorted */

void minimum_element_sort(int array[], int num_elements);
void bubble_sort(int array[], int num_elements);
int is_sorted(int array[], int num_elements);

/*
 * minimum_element_sort: sorts a list of integers in ascending order
 *                       using the selection sort algorithm.
 * argument: array: integer array to be sorted
 *           num_elements: the number of elements in the array to be sorted
 * return: void; The function sorts the array in place.
 */
void minimum_element_sort(int array[], int num_elements) {
    int start, smallest, i, temp;

    start = 0; /* Index to start findind the next smallest element. */

    /* While we haven't sorted every spot in the array */
    while (start < num_elements) {
        smallest = start;
        /* Search the unsorted portion of the array for the next smallest. */
        for (i = start; i < num_elements; i++) {
            if (array[i] < array[smallest]) {
                smallest = i;
            }
        }

        /* Swap the smallest element with the next unsorted index */
        temp = array[start];
        array[start] = array[smallest];
        array[smallest] = temp;

        /* Since we've sorted the element and set it at the original start
         * index, we increment the index that we look at next. */
        start++;
    }
    /* Check that the array was indeed sorted */
    assert(is_sorted(array, num_elements));
}

/*
 * bubble_sort: sorts a list of integers in ascending order
 *                       using the (optimized) bubble sort algorithm.
 * argument: array: integer array to be sorted
 *           num_elements: the number of elements in the array to be sorted
 * return: void; The function sorts the array in place.
 */
void bubble_sort(int array[], int num_elements) {

    int num_passes, new_num_passes, i, temp;
    
    num_passes = num_elements; /* We plan to go through every element once */
    while (num_passes > 1) {
        new_num_passes = 0;
        /* Move the largest value you find along the array to the end */
        for (i = 1; i < num_passes; i++) {
            if (array[i - 1] > array[i]) {
                temp = array[i];
                array[i] = array[i - 1];
                array[i - 1] = temp;
                new_num_passes = i; /* Move index back of elements to check */
            }
        }
        /* After every pass, all elements after the last swap are sorted */
        num_passes = new_num_passes;
    }
    /* Check that the array was indeed sorted */
    assert(is_sorted(array, num_elements));
}

/*
 * is_sorted: returns whether or not the array is sorted or not
 * argument: array: integer array to be checked for sortedness
 *           num_elements: the number of elements in the array
 * return: integer, 0 if not sorted, 1 if sorted.
 */
int is_sorted(int array[], int num_elements) {
    int i;
    /* Iterate through each adjacent pair to check if it is sorted */
    for (i = 0; i < num_elements - 1; i++) {
        if (array[i] > array[i + 1]) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    int i, num_elements, b_arg, q_arg;
    int array[MAX_N];       /* Declare array of maximum size */

    num_elements = 0;       /* Counter for number of elements */
    b_arg = 0;              /* Boolean for presence of -b argument */
    q_arg = 0;              /* Boolean for presence of -q argument */

    /* Iterate through each command-line argument except the first */
    for (i = 1; i < argc; i++) {

        /* Check for bubble sort argument */
        if (strcmp(argv[i], "-b") == 0) {
            b_arg = 1;
        } 
        /* Check for output suppression argument */
        else if (strcmp(argv[i], "-q") == 0) {
            q_arg = 1;
        }
        /* Process integer */
        else {
            /* If there is already the maximum number of elements, exit */
            if (num_elements == MAX_N) {
                fprintf(stderr, 
                "usage: %s [-b] [-q] "
                "number1 [number2 ...] (maximum 32 numbers)\n", 
                argv[0]);
                exit(1);
            } 

            /* Any command line argument that isn't -b or -q is assumed to
             * be an integer per the instructions */
            array[num_elements] = atoi(argv[i]);
            num_elements++;
        }
    }

    /* If there are no integer, exit */
    if (num_elements == 0) {
        fprintf(stderr, \
        "usage: %s [-b] [-q] number1 [number2 ...] (maximum 32 numbers)\n", \
        argv[0]);
        exit(1);
    } 

    /* Perform bubble sort instead of selection sort if -b is found */
    if (b_arg) {
        bubble_sort(array, num_elements);
    }
    else {
        minimum_element_sort(array, num_elements);
    }

    /* Suppress output if -q is found */
    if (!q_arg) {
        for (i = 0; i < num_elements; i++) {
            printf("%d\n", array[i]);
        }
    }
    return 0;
}