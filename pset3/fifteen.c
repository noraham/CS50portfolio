// Problem Set 3: Game of Fifteen. concepts demonstrated: create & call functions, control flow & looping, algorithmic problem-solving, conditional logic.
//
// This is my implementation of Game of Fifteen, a puzzle played on a square, two-dimensional board with numbered tiles that slide. 
// The goal of this puzzle is to arrange the board’s tiles from smallest to largest, left to right, top to bottom, 
// with an empty space in board’s bottom-right corner.
//
// To be clear, I wrote the code for the functions init, draw, move, and won. The rest of the code was given.
//
// fifteen.c and all content from CS50 is Copyright © 2015 – 2016, David J. Malan of Harvard University
// This course's content is licensed by David J. Malan of Harvard University under a Creative Commons Attribution-Noncommercial-Share
// Alike 3.0 Unported License, http://creativecommons.org/licenses/by-nc-sa/3.0/
//
// Specification: Implement init.
// Implement draw.
// Implement move.
// Implement won.
//
// Usage: $ ./fifteen [int]

/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    int numtile = d*d - 1;

    // iterate through rows
    for (int i = 0; i < d; i++)
    {
        //iterate through columns
        for (int j = 0; j < d; j++)
        {
            board[i][j] = numtile; //assign array values, descending
            numtile--;
        }

    }
    //test for even numbers, have to swap 2 and 1 position in this case
    if (d % 2 == 0)
    {
        int swap = board[d - 1][d - 3];
        board[d - 1][d - 3] = board[d - 1][d - 2];
        board[d - 1][d - 2] = swap;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // iterate through rows
    for (int i = 0; i < d; i++)
    {
        //iterate through columns
        for (int j = 0; j < d; j++)
        {
            //replace 0 with _
            if (board[i][j] == 0)
            {
                printf(" _ ");
            }
            else
            {
                printf("%2i ", board[i][j]); //print value assigned in init
            }
        } printf("\n"); //new line after each j loop finishes
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    //user enters number as (int tile), figure out corresponding array position
    // iterate through rows
    for (int i = 0; i < d; i++)
    {
        //iterate through columns
        for (int j = 0; j < d; j++)
        {
           if (board[i][j] == tile) //find array position that matches user input
           {
               if (board[i][j - 1] == 0 && j - 1 >= 0) //if blank is adjacent to user's tile input, swap array positions of tile and blank. the && statement is to make sure you can't go off the board
               {
                   board[i][j] = 0;
                   board [i][j - 1] = tile;
                   return true;
               }
               if (board[i][j + 1] == 0 && j + 1 <= d - 1) //same, different direction
               {
                   board[i][j] = 0;
                   board [i][j + 1] = tile;
                   return true;
               }
               if (board[i - 1][j] == 0 && i - 1 >= 0) //same, different direction
               {
                   board[i][j] = 0;
                   board [i - 1][j] = tile;
                   return true;
               }
               if (board[i + 1][j] == 0 && i + 1 <= d - 1) //same different direction
               {
                   board[i][j] = 0;
                   board [i + 1][j] = tile;
                   return true;
               }
           }
        }
    }
    return false; // if none of the if conditions above applied to user's input (tile input not on board or not adjacent to blank), returns false which prints illegal move and retry
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    // iterate over board checking values, if any mismatch, return false, return true once all tiles are checked
    //create formula for correct value
    int check = 1;

    // iterate through rows
    for (int i = 0; i < d; i++)
    {
        //iterate through columns
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == check)
            {
                check++;
            }
            if (check == d*d - 1 && board[d - 1][d - 1] == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Testing corectness (check50 results):
// :) fifteen.c exists.
// :) fifteen.c compiles.
// :) 3x3 board: init initializes board correctly
// :) 3x3 board: catches moving 8 an illegal move
// :) 3x3 board: catches moving 1 as a legal move
// :) 3x3 board: move blank up twice
// :) 3x3 board: move blank left twice
// :) 3x3 board: move blank left then right
// :) 3x3 board: move blank up then down
// :) 3x3 board: move up-up-left-down-down-left-up-up-right-down-down-right
// :) 3x3 board: make sure none of 2, 4, 5, 6, 7, 8 move tile
// :) 3x3 board: move blank left (tile 1) then up (tile 4), then try to move tiles 1, 2, 6, 8
// :) 3x3 board: make sure game is winnable
// :) 4x4 board: make sure game is winnable
