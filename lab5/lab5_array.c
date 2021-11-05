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

void randomly_seed(int *cell, int num_cells);
void update(int *cell, int *new_cells, int n_cells);
void compute_automata(int n_cells, int n_gens);
void print_usage_statement(char *function);

void randomly_seed(int *cell, int num_cells) {
    int i, randN;
    srand(time(0));
    for (i = 0; i < num_cells; i++) {
        randN = rand();

        if (randN <= RAND_MAX / 2) {
            cell[i] = 1;
        }
    }
}

void update(int *cell, int *new_cell, int n_cells) {
    int i;

    for(i = 1; i < n_cells - 1; i++) {
        if (cell[i] == 0 && (cell[i-1] != cell[i+1])) {
            new_cell[i] = 1;
        }
        else {
            new_cell[i] = 0;
        }
    }
}

void print_cells(int *cells, int n_cells) {
    int i;
    char *output;

    for(i = 0; i < n_cells; i++) {
        if (cells[i] == 1) {
            output = "*";
        }
        else {
            output = ".";
        }
        printf("%s", output);
    }
    printf("\n");
}

void compute_automata(n_cells, n_gens) {
    int *cell, *new_cell, i, *temp;

    cell = (int *)calloc(n_cells, sizeof(int));
    if (cell == NULL) {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);
    }

    new_cell = (int *)calloc(n_cells, sizeof(int));
    if (new_cell == NULL) {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);
    }

    randomly_seed(cell, n_cells);
    

    for(i = 0; i < n_gens; i++) {
        update(cell, new_cell, n_cells);
        print_cells(new_cell, n_cells);
        temp = cell;
        cell = new_cell;
        new_cell = temp;
    }

    free(cell);
    free(new_cell);
}

void print_usage_statement(char *function) {
    fprintf(stderr, "usage: %s number_cells number_generations" 
    "(positive integers)\n", function);
}

int main(int argc, char *argv[]) {
    int n_cells, n_gens;

    if (argc != 3) {
        print_usage_statement(argv[0]);
        exit(1);
    }

    n_cells = atoi(argv[1]);
    n_gens = atoi(argv[2]);

    if (n_cells < 0 || n_gens < 0) {
        print_usage_statement(argv[0]);
        exit(1);
    }

    compute_automata(n_cells, n_gens);
    print_memory_leaks();
    return 0;
}