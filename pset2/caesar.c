// Problem Set 2: Caesar. concepts demonstrated: control flow & looping, basic datatypes
//
// This is my implementation of Caesar, a program that encrypts messages using Caesar’s cipher.
//
// caesar.c and all content from CS50 is Copyright © 2015 – 2016, David J. Malan of Harvard University
// This course's content is licensed by David J. Malan of Harvard University under a Creative Commons Attribution-Noncommercial-Share
// Alike 3.0 Unported License, http://creativecommons.org/licenses/by-nc-sa/3.0/
//
// Specification: Your program must accept a single command-line argument, a non-negative integer.
// If your program is executed without any command-line arguments or with more than one command-line argument, your program should print
// an error message of your choice (with printf) and return from main a value of 1 (which tends to signify an error) immediately.
// You can assume that, if a user does provide a command-line argument, it will be a non-negative integer. No need to check that it’s 
// indeed numeric.
// Do not assume that k will be less than or equal to 26. Your program should work for all non-negative integral values of k less than 
// 231 - 26. In other words, you don’t need to worry if your program eventually breaks if the user chooses a value for k that’s too big
// or almost too big to fit in an int. (Recall that an int can overflow.) But, even if k is greater than 26, alphabetical characters in
// your program’s input should remain alphabetical characters in your program’s output, provided you wrap around from Z to A.
// Your program must output plaintext: (without a newline) and then prompt the user for a string of plaintext (using get_string).
// Your program must output ciphertext: (without a newline) followed by the plaintext’s corresponding ciphertext, with each alphabetical
// character in the plaintext "rotated" by k positions; non-alphabetical characters should be outputted unchanged.
// Your program must preserve case: capitalized letters, though rotated, must remain capitalized letters; lowercase letters, though
// rotated, must remain lowercase letters.
// After outputting ciphertext, you should print a newline. Your program should then exit by returning 0 from main.
//
// Usage: $ ./caesar [cipher int]

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //reject attempt if there are not 2 user inputs on the command line
    if (argc != 2)
    {
        printf ("retry\n");
        return 1;
    }

    //convert user's command line input from string to integer
    int c = atoi(argv[1]);

    //get plaintext from user, store as string
    printf ("plaintext: ");
    string pt = get_string();

    printf ("ciphertext: ");

    //iterate through pt, rotating by argv (stored as int c) positions
    for (int i = 0, n = strlen(pt); i < n; i++)
    {
        //alter alpha chars
        if (isalpha (pt[i]))
        {
            if (islower (pt[i]))
            {
                int y = pt[i] - 97;
                int yy = (y + c) % 26;
                printf ("%c", yy + 97);
            }

            if (isupper (pt[i]))
            {
                int x = pt[i] - 65;
                int xx = (x + c) % 26;
                printf ("%c", xx + 65);
            }
        }
        //preserve non-alpha chars
        else
        {
            printf ("%c", pt[i]);
        }
    }

    printf ("\n");
    return 0;
}

// Testing corectness (check50 results):
// :) caesar.c exists.
// :) caesar.c compiles.
// :) encrypts "a" as "b" using 1 as key
// :) encrypts "barfoo" as "yxocll" using 23 as key
// :) encrypts "BARFOO" as "EDUIRR" using 3 as key
// :) encrypts "BaRFoo" as "FeVJss" using 4 as key
// :) encrypts "barfoo" as "onesbb" using 65 as key
// :) handles lack of argv[1]
