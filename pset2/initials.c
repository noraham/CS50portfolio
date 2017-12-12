// Problem Set 2: Initials. concepts demonstrated: basic datatypes, control flow & looping
//
// This is my implementation of Initials, a program that, given a person’s name, prints a person’s initials.
//
// initials.c and all content from CS50 is Copyright © 2015 – 2016, David J. Malan of Harvard University
// This course's content is licensed by David J. Malan of Harvard University under a Creative Commons Attribution-Noncommercial-Share
// Alike 3.0 Unported License, http://creativecommons.org/licenses/by-nc-sa/3.0/
//
// Specification: Your program should prompt a user for their name using get_string to obtain their name as a string.
// You may assume that the user’s input will contain only letters (uppercase and/or lowercase) plus single spaces between words. 
// You don’t need to worry about names like Joseph Gordon-Levitt, Conan O’Brien, or David J. Malan!
// Your program should print the user’s initials with no spaces or periods, followed by a newline (\n).
//
// Usage: $ ./initials

#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (void)
{
    //get name from user, store as string
    string s = get_string();

    //print first letter of string, capitalized
    printf("%c", toupper(s[0]));

    //iterate over each char in the string one by one
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //if you find a space, print the next char in the string, capitalized
        if (s[i] == ' ')
        {
            printf ("%c", toupper(s[i + 1]));
        }
    }
    //spec requires new line at end
    printf ("\n");
}

// Testing corectness (check50 results):
// :) initials.c exists.
// :) initials.c compiles.
// :) Outputs HLJ for Hailey Lynn James
// :) Outputs HLJ for hailey lynn james
// :) Outputs HJ for hailey James
// :) Outputs B for BRIAN
