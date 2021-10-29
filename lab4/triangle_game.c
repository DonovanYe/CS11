/* Donovan Ye
 * CS 11: C Track
 * Lab 4: Triangle Game
 *
 * This program:
 *      - Gets an initial board from the user represented as a 1D array of ints
 *          - 0 means there is no peg
 *          - 1 means there is a peg
 *      - The Triangle Game is a solitaire board game played on a triangular 
 *          board with fifteen equally spaced holes in it.
 *          - A peg can move by jumping over an adjacent peg which is then 
 *              removed.
 *          - The only way to move a peg is to jump over an adjacent peg
 *              into an empty space
 *      - Finds out if there is a set of moves that leave only one peg
 *          - If no set exists, report and exit
 *          - If at least one set of moves exist, print out the board positions
 *              that the moves go through, starting with a single peg,
 *              and ending with the user supplied board.
 *          - i.e. prints the solution out in reverse order
 *
 */

#include <stdio.h>
#include "triangle_routines.h"

#define NMOVES 36   /* Number of possible moves */
#define NHOLES 15   /* Number of holes in the board */

/* All possible moves that can be made in the triangle game */
int moves[NMOVES][3] = {
    {0, 1, 3}, {3, 1, 0},
    {0, 2, 5}, {5, 2, 0},
    {1, 3, 6}, {6, 3, 1},
    {1, 4, 8}, {8, 4, 1},
    {2, 4, 7}, {7, 4, 2},
    {2, 5, 9}, {9, 5, 2},
    {3, 4, 5}, {5, 4, 3},
    {3, 6, 10}, {10, 6, 3},
    {3, 7, 12}, {12, 7, 3},
    {4, 7, 11}, {11, 7, 4},
    {4, 8, 13}, {13, 8, 4},
    {5, 8, 12}, {12, 8, 5},
    {5, 9, 14}, {14, 9, 5},
    {6, 7, 8}, {8, 7, 6},
    {7, 8, 9}, {9, 8, 7},
    {10, 11, 12}, {12, 11, 10},
    {11, 12, 13}, {13, 12, 11},
    {12, 13, 14}, {14, 13, 12}
};

/* ---------------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 * ---------------------------------------------------------------------------
 */

/* Checks if the contents of two int arrays are the same.  */
int int_arrays_equal(int a[], int b[], int size_a, int size_b);

/* Return the number of pegs on the board. */
int npegs(int board[]);

/* Return 1 if the move is valid on this board, otherwise return 0. */
int valid_move(int board[], int move[]);

/* Make this move on this board. */
void make_move(int board[], int move[]);

/* Unmake this move on this board. */
void unmake_move(int board[], int move[]);

/*
 * Solve the game starting from this board.  Return 1 if the game can
 * be solved; otherwise return 0.  Do not permanently alter the board passed
 * in. Once a solution is found, print the boards making up the solution in
 * reverse order.
 */
int solve(int board[]);

/* ---------------------------------------------------------------------------
 * FUNCTIONS
 * ---------------------------------------------------------------------------
 */

/*
 * int_arrays_equal: Checks if the contents of two integer arrays are the same.
 * args: int a[]: the first array to check
 *         int b[]: the second array to check
 *        int size_a: the size of the first array
 *        int size_b: the size of the second array
 * return: int: 1 if they are they same, 0 otherwise
 */
int int_arrays_equal(int a[], int b[], int size_a, int size_b) {
    int i;

    /* If the sizes don't match, the contents will never match. */
    if (size_a != size_b) {
        return 0;
    }

    /* Check each corresponding index for equality */
    for(i = 0; i < size_a; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }

    return 1;
}


/*  
 *  npegs: Gets the number of pegs on the board.
 *  args: int board[]: the game board as an int[15]; where 1 means there's a
 *                       peg and 0 means that the space is empty
 *  return: int: the number of pegs in the board
 */
int npegs(int board[]) {
    int i;
    int pegs; /* Number of pegs */

    /* Loop through the board and summing elements since 1=peg, 0=empty. */
    pegs = 0;
    for(i = 0; i < NHOLES; i++) {
        pegs += board[i];
    }

    return pegs;
}

/*  
 *  valid_move: Checks if a move is valid in a given board.
 *  args: int board[]: the game board as an int[15]; where 1 means there's a
                        peg and 0 means that the space is empty
          int move[]: array of three ints that represent the move to be checked
 *  return: int: 1 if the move is valid, 0 if the move is invalid
 */
int valid_move(int board[], int move[]) {
    int i;
    
    /* Check if the move is a valid move in general */
    for (i = 0; i < NMOVES; i++) {
        if (int_arrays_equal(move, moves[i], NHOLES, NHOLES)) {
            /* Check for pegs in the first two holes, but empty in the last. */
            return board[move[0]] == 1 && \
                    board[move[1]] == 1 && \
                    board[move[2]] == 0;
        }
    }

    return 0;
}

/* make_move: Make this move on this board. 
 *  args: int board[]: the game board as an int[15]; where 1 means there's a
 *                       peg and 0 means that the space is empty
 *        int move[]: the array of three ints that represents the move
 * return: void; changes the board array in place         
 */
void make_move(int board[], int move[]) {
    /* Make a move means, moving peg in first position to third position, 
     * meaning the first position is now empty and the third position is 
     * filled. The middle peg that was jumped over is now empty. 
     */
    board[move[0]] = 0;
    board[move[1]] = 0;
    board[move[2]] = 1;
}

/* make_move: Unmake this move on this board. 
 *  args: int board[]: the game board as an int[15]; where 1 means there's a
 *                       peg and 0 means that the space is empty
 *        int move[]: the array of three ints that represents the move
 * return: void; changes the board array in place         
 */
void unmake_move(int board[], int move[]) {
    /* Unmaking a move means, moving the peg in the third position back to the
     * first position, meaning the third position is now empty and the first
     * position is filled again. The middle peg is then returned to be filled.
     */
    board[move[0]] = 1;
    board[move[1]] = 1;
    board[move[2]] = 0;
}

/*
 * solve: Solve the game starting from this board, if it can be solved.  
 * args: int board[]: the game board as an int[15]; where 1 means there's a
 *                       peg and 0 means that the space is empty
 * return: Return 1 if the game can be solved; otherwise return 0.  
 *         Does alter the board passed in. 
 *         If a solution exists, print the boards making up the solution in
 *              reverse order.
 */
int solve(int board[]) {
    int i;
    int solvable; /* Boolean for whether the board is solvable */

    /* Base Case: There is one peg left. */
    if (npegs(board) == 1) {


        /* If the board has one peg left, it is solved. "Tell" the previous
         * board state that called this recursive call that it's part of a 
         * valid solution by returning 1.
         */
        triangle_print(board);
        return 1;
    }

    /* Recursive Step: Basically DFS down each possible valid move.
     * Once a valid final board is found, backtrack all the way to input board,
     * printing the board state along the way.
     */

    /* Check every possible move */
    for(i = 0; i < NMOVES; i++) {
        /* Check every possible *valid* move */
        if (valid_move(board, moves[i])) {

            /* Make that move */
            make_move(board, moves[i]);

            /* Try to solve a board where that move was made */
            solvable = solve(board);

            /* Undo that move that was made */
            unmake_move(board, moves[i]);

            /* If the board that was attempted yields a solution, print this
             * "move" i.e. the state of this board. And "tell" the previous
             * board state that it's part of a valid solution by returning 1.
             */
            if (solvable) {
                triangle_print(board);
                return solvable;
            }
        }
    }

    /* If all possible moves don't yield a solution path, it is unsolvable. */
    return 0;
}

int main(void)
{
    int board[BOARD_SIZE];  /* Declare board with 15 empty holes */
    int solvable;           /* Boolean for whether the board is solvable */

    triangle_input(board);  /* Fill in the board with pegs */
    solvable = solve(board);           /* Solve the board */

    /* If not solvable, report */
    if (!solvable) {
        printf("The board is not solvable. \n");
    }
    return 0;
}