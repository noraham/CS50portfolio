// Problem Set 3: Find. concepts demonstrated: algorithmic problem-solving, create & call functions, conditional logic
//
// This is my implementation of Find, a program that finds a number among numbers. To be used with helpers.h and find.c, which were given.
//
// helpers.c and all content from CS50 is Copyright © 2015 – 2016, David J. Malan of Harvard University
// This course's content is licensed by David J. Malan of Harvard University under a Creative Commons Attribution-Noncommercial-Share
// Alike 3.0 Unported License, http://creativecommons.org/licenses/by-nc-sa/3.0/
//
// Specification: Complete the implementation of find by completing the implementation of Search and Sort in helpers.c.
// Search:
// Your implementation must return false immediately if n is non-positive.
// Your implementation must return true if value is in values and false if value is not in values.
// The running time of your implementation must be in O(log n).
// You may not alter the function’s declaration.
// Sort:
// Your implemenation must sort, from smallest to largest, the array of numbers that it’s passed.
// The running time of your implementation must be in O(n2), where n is the array’s size.
// You may not alter the function’s declaration.
//
// Usage: $ ./find [int]

/**
 * helpers.c, to be used with find.c and helpers.h
 */
#include <cs50.h>
#include "helpers.h"
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n <= 0) // return false if n is non-pos
    {
        return false;
    }

    // need to get these 2 set up
    int start = 0;
    int end = n - 1;

    while (end >= start) // if end less than start, means value is not in stack, and we will be in ifinite loop unless we have this condition to break us out
    {
        int mid = (start + end) / 2; // a new middle value will be created with each loop

        if (values[mid] == value)
        {
            return true;
        }
        else if (values[mid] < value) // if needle is on right side of stack, move start over and loop again
        {
            start = mid + 1;
        }
        else if (values[mid] > value) // if needle is on left side of stack, move end over and loop again
        {
            end = mid - 1;
        }
    }

    return false; // if we have broken out of the while loop it means the needle is not in the stack and we will return false value to signal that
}

/**
 * Sorts array of n values with bubble sort method.
 */
void sort(int values[], int n)
{
    int count = -1; // neet to start swap counter at not 0 so it will enter the while loop

    do
    {
        count = 0; // have to reset swap counter to 0 for each loop
        for (int i = 0; i < n - 1; i++) // iterate through each value in array, n decreases with each pass?
        {

            if (values[i] > values[i + 1]) // if the values are out of order, create a free space with the added integer and move values around by reassigning
            {
                int swap = values[i];
                values[i] = values[i + 1];
                values[i + 1] = swap;
                count++; //adds to the swap count if a swap was made
            }
        }
    }
    while (count != 0); // when no longer making swaps, break out of loop

    return;
}

// Testing corectness (check50 results):
// :) helpers.c exists.
// :) helpers.c compiles.
// :) sorts {5,4,3,2,1}
// :) sorts {5,3,1,2,4,6}
// :) finds 28 in {28,29,30}
// :) finds 28 in {27,28,29}
// :) finds 28 in {26,27,28}
// :) finds 28 in {27,28,29,30}
// :) finds 28 in {26,27,28,29}
// :) finds 28 in {25,26,27,28}
// :) doesn't find 28 in {25,26,27}
// :) doesn't find 28 in {25,26,27,29}
// :) doesn't find 28 in {29,30,31,32}
// :) doesn't find 28 in {29, 30, 31}
// :) finds 28 in {30,27,28,26}
