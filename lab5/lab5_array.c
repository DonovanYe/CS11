#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "memcheck.h"

/* Donovan Ye
 * CS 11: C Track
 * THIS FILE: lab5_array.c
 *
 * This program doesn the following:
 *      - Implements a 1 dimensional cellular automata with the following rules:
 *          - If the current cell is empty, and one of the two adjacent cells
 *              is full (but not both), set the current cell to be full
 *          - Otherwise, set the current cell to be empty
 *      - An empty cell is represented by a 0 visualized as '.'
 *      - A full cell is represented by a 1 visualized as '1'.
 *      - This program takes two command line arguments:
 *          - an int that represents the number of cells in the 1dCA
 *          - an int that represents the number of generations to compute.
 *      - The first generation is randomly seeded.
 *      - This program will use array operations.
 */

/* ---------------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 * ---------------------------------------------------------------------------
 */

/* Randomly fill array with 0's and 1's. */
void randomly_seed(int *cell, int num_cells);
/* Iterate one generation of the automata. */
void produce_generation(int *cell, int *new_cells, int n_cells);
/* Output a state of the automata with corresponding characters. */
void print_cells(int *cell, int n_cells);
/* Compute all generations of the automata and print result. */
void compute_automata(int n_cells, int n_gens);
/* Prints usage statement to stderr. */
void print_usage_statement(char *program_name);
/* Handle the case where malloc/calloc returns NULL */
void handle_null_allocaction(void *ptr);

/* ---------------------------------------------------------------------------
 * FUNCTION IMPLEMENTATION
 * ---------------------------------------------------------------------------
 */

/*
 * randomly_seed: Randomly assigns values in an int array to either 0 or 1.
 * args: int *cell: pointer to array to seed
 *       int num_cells: number of values in the array
 * return: void, overwrites "cell"
 */
void randomly_seed(int *cell, int num_cells) {
    int i;

    /* Seed random with time. */
    srand(time(0));

    /* Fill each index with 0 or 1. */
    for (i = 0; i < num_cells; i++) {
        cell[i] = rand() % 2;
    }
}

/*
 * produce_generation: Produces a new generation according to the rules:
 *          - If the current cell is empty, and one of the two adjacent cells
 *              is full (but not both), set the current cell to be full
 *          - Otherwise, set the current cell to be empty
 *          - Empty = 0; Full = 1
 * args: int *cell: pointer to array for the basis for new generation
 *       int *new_cell: pointer to array to hold new generation
 *       int n_cells: number of cells in arrays; arrays should be same length
 * return: void, overwrites "new_cell"
 */
void produce_generation(int *cell, int *new_cell, int n_cells) {
    int i;

    for(i = 1; i < n_cells - 1; i++) {
        /* If empty and only one filled, adjacent cell */
        if (cell[i] == 0 && (cell[i - 1] != cell[i + 1])) {
            new_cell[i] = 1;
        }
        else {
            new_cell[i] = 0;
        }
    }
}

/*
 * print_cells: Prints out all cells of a generation on one line.
 *          - Prints "." for 0
 *          - Prints "*" for 1
 * args: int *cell: pointer to array to print out
 *       int n_cells: number of cells in array
 * return: void, prints directly to output
 */
void print_cells(int *cells, int n_cells) {
    int i;
    char *output;

    for(i = 0; i < n_cells; i++) {
        if (cells[i] == 1) {
            /* 1 corresponds to "*" */
            output = "*";
        }
        else {
            /* 0 corresponds to "." */
            output = ".";
        }
        /* Note: No new line since each cell is on the same line. */
        printf("%s", output);
    }
    printf("\n");
}

/*
 * compute_automata: Runs the all the generations and prints them out
 * args: int n_cells: number of cells in the automata
         int n_gens: number of generations to compute
 * return: void, prints generations (including gen 0) to output.
 */
void compute_automata(n_cells, n_gens) {
    int *cell, *new_cell, i, *temp;

    /* Allocate memory for "original" cells. */
    cell = (int *)calloc(n_cells, sizeof(int));
    handle_null_allocaction((void *)cell);

    /* Allocate memory for new generation of cells. */
    new_cell = (int *)calloc(n_cells, sizeof(int));
    handle_null_allocaction((void *)new_cell);

    /* Seed the original cells, and print them to output. */
    randomly_seed(cell, n_cells);
    print_cells(cell, n_cells);

    /* Produce new generations. */
    for(i = 0; i < n_gens; i++) {
        produce_generation(cell, new_cell, n_cells);
        print_cells(new_cell, n_cells);
        /* Since a new generation uses "cell" as a base, assign the newly
         * generated generation to "cell", i.e. swap them (using a temp). */
        temp = cell;
        cell = new_cell;
        new_cell = temp;
    }

    /* Free allocated memory. */
    free(cell);
    free(new_cell);
}

/*
 * print_usage_statement: Prints usage statement to stderr
 * args: char *program_name: name of the program called (this program)
 * return: void, prints directly to stderr
 */
void print_usage_statement(char *program_name) {
    fprintf(stderr, "usage: %s arg1 arg2\n"
        "\targ1: Number of cells (positive int)\n"
        "\targ2: Number of generations (positive int)\n", program_name); 
}

/*
 * print_usage_statement: Appropriately handles the case where 
 *                          malloc/calloc returns NULL.
 * args: void *ptr, pointer returned from malloc/calloc to check
 * return: void, prints error to stderr and exits the program.
 */
void handle_null_allocaction(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    int n_cells, n_gens;

    /* If there are fewer than 3 arguments, (program, number of cells, and 
     * number of generations), there this is an incorrect use of the program. */
    if (argc != 3) {
        print_usage_statement(argv[0]);
        exit(1);
    }

    /* We're assuming that ints are being passed. */
    n_cells = atoi(argv[1]);
    n_gens = atoi(argv[2]);

    /* If the command-line arguments are negative, indicate incorrect call. */
    if (n_cells < 0 || n_gens < 0) {
        print_usage_statement(argv[0]);
        exit(1);
    }

    /* Run the automata. */
    compute_automata(n_cells, n_gens);

    /* Check for memory leaks. */
    print_memory_leaks();

    return 0;
}