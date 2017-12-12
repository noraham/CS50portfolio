// Problem Set 2: Vigenere. concepts demonstrated: control flow & looping, basic datatypes
//
// This is my implementation of Vigenere, a program that encrypts messages using Vigenère’s cipher.
//
// vigenere.c and all content from CS50 is Copyright © 2015 – 2016, David J. Malan of Harvard University
// This course's content is licensed by David J. Malan of Harvard University under a Creative Commons Attribution-Noncommercial-Share
// Alike 3.0 Unported License, http://creativecommons.org/licenses/by-nc-sa/3.0/
//
// Specification: Your program must accept a single command-line argument: a keyword, k, composed entirely of alphabetical characters.
// If your program is executed without any command-line arguments, with more than one command-line argument, or with one command-line 
// argument that contains any non-alphabetical character, your program should print an error (of your choice) and exit immediately, 
// with main returning 1 (thereby signifying an error).
// Otherwise, your program must proceed to prompt the user for a string of plaintext, p, which it must then encrypt according to 
// Vigenère’s cipher with k, ultimately printing the result and exiting, with main returning 0.
// With respect to the characters in k, you must treat A and a as 0, B and b as 1, Z and z as 25, etc.
// Your program must only apply Vigenère’s cipher to a character in p if that character is a letter. All other characters (numbers, 
// symbols, spaces, punctuation marks, etc.) must be outputted unchanged. Moreover, if your code is about to apply the jth character of 
// k to the ith character of p, but the latter proves to be a non-alphabetical character, you must wait to apply that jth character of k 
// to the next alphabetical character in p; you must not yet advance to the next character in k.
// Your program must preserve the case of each letter in p.
//
// Usage: $ ./vigenere [cipher keyword(s)]

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

    string c = argv[1]; //convert cipher to string c
    int cc = strlen (c);

    //reject attempt if argv (stored as str c) is not aplha
    for (int a = 0; a < cc; a++)
    {
        if (isalpha (c[a]))
        {
            continue; //do nothing
        }
        else
        {
            printf ("retry\n");
            return 1;
        }
    }

    //convert cipher to all uppercase
    for (int e = 0; e < cc; e++)
    {
        c[e] = toupper (c[e]);
    }

    //get plaintext from user, store as string
    printf ("plaintext: ");
    string pt = get_string();

    printf ("ciphertext: ");

    //iterate through pt, shifting by cipher
    for (int i = 0, n = strlen(pt), d = 0; i < n; i++)
    {
        //alter alpha chars
        if (isalpha (pt[i]))
        {
            if (islower (pt[i]))
            {
                int y = pt[i] - 97;
                int yy = (y + (c[(d % cc)] - 65)) % 26;
                printf ("%c", yy + 97);
                d++;
            }

            if (isupper (pt[i]))
            {
                int x = pt[i] - 65;
                int xx = (x + (c[(d % cc)] - 65)) % 26;
                printf ("%c", xx + 65);
                d++;
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
// :) vigenere.c exists.
// :) vigenere.c compiles.
// :) encrypts "a" as "a" using "a" as keyword
// :) encrypts "barfoo" as "caqgon" using "baz" as keyword
// :) encrypts "BaRFoo" as "CaQGon" using "BaZ" as keyword
// :) encrypts "BARFOO" as "CAQGON" using "BAZ" as keyword
// :) encrypts "world!$?" as "xoqmd!$?" using "baz" as keyword
// :) handles lack of argv[1]
// :) handles argc > 2
// :) rejects "Hax0r2" as keyword
