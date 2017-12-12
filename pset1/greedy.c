// Problem Set 1: Greedy. concepts demonstrated: basic data types

// This is my implementation of Greedy, a program that calculates the minimum number of coins required to give a user change.
//
// greedy.c and all content from CS50 is Copyright © 2015 – 2016, David J. Malan of Harvard University
// This course's content is licensed by David J. Malan of Harvard University under a Creative Commons Attribution-Noncommercial-Share
// Alike 3.0 Unported License, http://creativecommons.org/licenses/by-nc-sa/3.0/
//
// Specification: Write a program that first asks the user how much change is owed and then spits out 
// the minimum number of coins with which said change can be made.
// Use get_float from the CS50 Library to get the user’s input and printf from the Standard I/O library to output your answer. 
// Assume that the only coins available are quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢).
// You need not worry about checking whether the user’s input is "formatted" like money should be.
// You need not try to check whether a user’s input is too large to fit in a float.
// If the user fails to provide a non-negative value, your program should re-prompt the user for a valid amount until the user complies.
// Incidentally, so that we can automate some tests of your code, we ask that your program’s last line of output be 
// only the minimum number of coins possible: an integer followed by \n.
//
// Usage: $ ./greedy

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;
    do
    {
        printf("How much change is owed? ");
        change = get_float(); //using data type float so input can be in dollars and cents
    }
    while (change < 0); //repeat prompt if a negative value is entered, repeat until we have acceptable input

    change *= 100; //convert input to cents
    int cent = round(change); //prevent floating point imprecision (gets rid of stray numbers) by rounding

    int qcoin, qrem, dcoin, drem, ncoin, nrem, pcoin, prem, count;
    qcoin = cent / 25; //start with largest coin since we want to return the lowest amount of coins as possible. calc number of quarters to give user
    qrem = cent % 25; //use % modulo to give remainder of the division operation, pass that to next largest coin type.
    printf("%i %i\n", qcoin, qrem);
    dcoin = qrem / 10; //calc number of dimes to give user
    drem = qrem % 10;
    printf("%i %i\n", dcoin, drem);
    ncoin = drem / 5; //calc number of nickels to give user
    nrem = drem % 5;
    printf("%i %i\n", ncoin, nrem);
    pcoin = nrem / 1; //how many pennies the user gets
    prem = nrem % 1; //calc and print this value just to check that calculations are working properly (should always be 0)
    printf("%i %i\n", pcoin, prem);
    count = qcoin + dcoin + ncoin + pcoin; //sum number of each coin type to get minimum number of coins possible.
    printf("%i\n", count);
}

// Testing corectness (check50 results):
// :) greedy exists
// :) greedy compiles
// :) input of 0.41 yields output of 4
// :) input of 0.01 yields output of 1
// :) input of 0.15 yields output of 2
// :) input of 1.6 yields output of 7
// :) input of 23 yields output of 92
// :) input of 4.2 yields output of 18
// :) rejects a negative input like -.1
// :) rejects a non-numeric input of "foo"
// :) rejects a non-numeric input of ""
