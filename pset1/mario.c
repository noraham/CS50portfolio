// Problem Set 1: Mario. concepts demonstrated: control flow & looping
//
// This is my implementation of Mario, a program that prints out a half-pyramid of a specified height, inspired by the "half-pyramid" of
// blocks that Mario must ascend at the end of World 1-1 in Nintendo’s Super Mario Brothers.
//
// mario.c and all content from CS50 is Copyright © 2015 – 2016, David J. Malan of Harvard University
// This course's content is licensed by David J. Malan of Harvard University under a Creative Commons Attribution-Noncommercial-Share
// Alike 3.0 Unported License, http://creativecommons.org/licenses/by-nc-sa/3.0/
//
// Specification: Write a program that recreates the Mario half-pyramid using hashes (#) for blocks.
// To make things more interesting, first prompt the user for the half-pyramid’s height, a non-negative integer no greater than 23.
// If the user fails to provide a non-negative integer no greater than 23, you should re-prompt for the same again.
// Then, generate (with the help of printf and one or more loops) the desired half-pyramid.
// Take care to align the bottom-left corner of your half-pyramid with the left-hand edge of your terminal window.
//
// Usage: $ ./mario

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do // do/while loop
    {
        printf("Height:");
        n = get_int(); //get input from user, store in int n
    }
    while (n > 23 || n < 0); //continue to reprompt user for Height until you have acceptable input (defined in Specification)

    for (int x = 0; x < n; x++) //dictates the number of lines in the pyramid, iterates through each line
    {
        for (int sp = 1; sp < n - x; sp++) //formula for this line's spaces, which decreases with each loop
        {
            printf(" ");
        }
        for (int bl = 0; bl < (n + 2) - (n - x); bl++) //formula for this line's blocks, which increases with each loop
        {
            printf("#");
        }
        printf("\n"); //move cursor to new line each time this loop completes
    } //we pop out of the for loop when the specified height is reached
}

// Testing corectness (check50 results):
// :) mario.c exists.
// :) mario.c compiles.
// :) rejects a height of -1
// :) handles a height of 0 correctly
// :) handles a height of 1 correctly
// :) handles a height of 2 correctly
// :) handles a height of 23 correctly
// :) rejects a height of 24, and then accepts a height of 2
// :) rejects a non-numeric height of "foo"
// :) rejects a non-numeric height of ""
