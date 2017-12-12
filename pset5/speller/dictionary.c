// Problem Set 5: Speller. concepts demonstrated: lists & arrays, create & call functions, algorithmic problem-solving, conditional logic
//
// This is my implementation of Speller, a program that spell-checks a file. 
// To be clear, I wrote the functions in dictionary.c called load, check, size, and unload, the rest was given.
//
// dictionary.c and all content from CS50 is Copyright © 2015 – 2016, David J. Malan of Harvard University
// This course's content is licensed by David J. Malan of Harvard University under a Creative Commons Attribution-Noncommercial-Share
// Alike 3.0 Unported License, http://creativecommons.org/licenses/by-nc-sa/3.0/
//
// Specification: Implement load.
// Implement check.
// Implement size.
// Implement unload.
//
// Usage: $ ./speller dictionary.txt text.txt

/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

//need to declare node struct up top so I can use it in all functions
typedef struct node //need to define what each node will contain, have to call node here because we call it inside the curly brackets
    {
        char word[LENGTH + 1]; //top half of node will be variable called word, which is an array of type char. size of array is LENGTH + 1 which represents longest known word+\0
        struct node *next; //bottom half of node is a pointer to another node, the pointer is called next
    }
    node;

node *hashtable[26]; //setting up hashtable, which will be an array of 26 node pointers, one for each letter in alpha, declare it up here so I can use it in multiple functions

int wordcount; //use to count words in dictionary, declared up here because used by load and size functions

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int same;
    char wordtocheck[LENGTH + 1]; //create this array here so we can use it below
    strcpy(wordtocheck, word); //converted the input string to an array of chars
        if(isupper(wordtocheck[0])) //need to convert first letter of word to lower or my hash function (index) won't work. 
        // only need to do this for first char because we are using strcasecmp to compare the strings, which is case-insensitive so other capitalizations won't cause false misspell flags.
        {
            wordtocheck[0] = tolower(wordtocheck[0]);
        }

    int index = wordtocheck[0] - 97; //same hash function as load, will bring us to the correct pointer for the letter
    node *cursor = hashtable[index]; //cursor will search the linked list and compare the input word with words in node
    while (cursor != NULL) //null means end of linked list, if cursor went all the way through linked list and found no matches, means input word is not in dictionary
    {
        same = strcasecmp(word, cursor->word); //strcasecmp returns 0 if the strings match, and a pos or neg integer if they don't match
        cursor = cursor->next; //cursor continues to next node in linked list
        if (same == 0)
        {
            return true; //input word matches a word loaded in the given dictonary
        }
    }
    return false; //input word was not found in the dictionary
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    char newword[LENGTH + 1]; //make this array of chars so we can use it in the while loop
    FILE *file = fopen(dictionary, "r");
    while (fscanf(file, "%s", newword) != EOF) //scan dictionary file, word by word (stored as string), save word in tempvariable called word, keep going till EOF
    {
        node *new_node = malloc(sizeof(node)); //each word scanned gets new node
        if (new_node == NULL) //safeguard in case we run out of memory, if that happens, we want to unload(free) the file and allocated memory, and stop the process
        {
            unload();
            return false;
        }
        strcpy(new_node->word, newword); //if malloc node succeeded, copy the string (called newword) into the word section of the new node
        new_node->next = NULL; //fill the pointer of new node with NULL as default, can replace later if we need to
        wordcount++;

        //hash function (adapted from Hash Tables Tutorial for Complete Beginners on go4expert.com)
        //hash function: takes first letter of word (key), converts that to an index, which will match a space in the hash array
        int index = newword[0] - 97; //I know that all words in the dictionary are in lowercase, therefore safe to use fixed value here,
        // will return an index between 0 and 25, whcih will fit in my hashtable array.
        if (index < 0)
        {
            printf("Error in hash function\n");
            return 1;
        }

        // add word to linked list
        if (hashtable[index] == NULL) //this pointer isn't pointing at anything: linked list hasn't been started for this letter/space in hashtable
        {
            hashtable[index] = new_node; //link these two to start the linked list
        }
        else //means the head pointer is pointing at something, insert new value at front of list
        {
            new_node->next = hashtable[index]; //make sure you duplicate the head pointer before reassigning the head pointer, or you will lose the rest of the linked list
            hashtable[index] = new_node; //reassign head pointer to new node, which is linked to the previously established linked list of nodes
        }
    }
    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordcount;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i <= 25; i++) //cant call index of hashtable, so have to get at it this way. we know it has 0-25 spaces, so just iterate theough each of those in order
    {
        node *cursor = hashtable[i]; //gets to the start of the linked list
        while (cursor != NULL) //when cursor == NULL we are at the end of the linked list, which means we are ready to move to next 'letter' in hashtable
        {
            node *temp = cursor; //grabs the location where cursor is pointing
            cursor = cursor->next; //cursor follows current node's next pointer (do this before freeing so that we don't lose linked list chain)
            free(temp); //free the node
        }
    }
    return true;
}

// Testing corectness (check50 results):
// :) dictionary.c, dictionary.h, and Makefile exist
// :) speller compiles
// :) handles most basic words properly
// :) handles min length (1-char) words
// :) handles max length (45-char) words
// :) handles words with apostrophes properly
// :) spell-checking is case-insensitive
// :) handles substrings properly
