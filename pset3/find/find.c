// This is (part of) my implementation of Find, a program that finds a number among numbers.
// This file was not made or edited by me, I made helpers.c which has the sort and search functions called here.
//
// find.c and all content from CS50 is Copyright © 2015 – 2016, David J. Malan of Harvard University
// This course's content is licensed by David J. Malan of Harvard University under a Creative Commons Attribution-Noncommercial-Share
// Alike 3.0 Unported License, http://creativecommons.org/licenses/by-nc-sa/3.0/
//
// Usage: $ ./find [int]

/**
 * Prompts user for as many as MAX values until EOF is reached, 
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

// maximum amount of hay
const int MAX = 65536;

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./find needle\n");
        return -1;
    }

    // remember needle
    int needle = atoi(argv[1]);

    // fill haystack
    int size;
    int haystack[MAX];
    for (size = 0; size < MAX; size++)
    {
        // wait for hay until EOF
        printf("\nhaystack[%i] = ", size);
        int straw = get_int();
        if (straw == INT_MAX)
        {
            break;
        }
     
        // add hay to stack
        haystack[size] = straw;
    }
    printf("\n");

    // sort the haystack
    sort(haystack, size);

    // try to find needle in haystack
    if (search(needle, haystack, size))
    {
        printf("\nFound needle in haystack!\n\n");
        return 0;
    }
    else
    {
        printf("\nDidn't find needle in haystack.\n\n");
        return 1;
    }
}
