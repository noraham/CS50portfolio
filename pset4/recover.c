// Problem Set 4: Recover. concepts demonstrated: lists & arrays, conditional logic
//
// This is my implementation of Recover, a program that recovers JPEGs from a forensic image. We are given a .raw file that represents a 
// camera memory card that has been 'deleted', and we write a program to recover the deleted photos.
//
// recover.c and all content from CS50 is Copyright © 2015 – 2016, David J. Malan of Harvard University
// This course's content is licensed by David J. Malan of Harvard University under a Creative Commons Attribution-Noncommercial-Share
// Alike 3.0 Unported License, http://creativecommons.org/licenses/by-nc-sa/3.0/
//
// Specification: Your program should accept exactly one command-line argument, the name of a forensic image from which to recover JPEGs.
// If your program is not executed with exactly one command-line argument, it should remind the user of correct usage, and main should
// return 1.
// If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return 2.
//
// Usage: $ ./recover card.raw

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "incorrect usage\n");
        return 1;
    }

     // open memory card
    FILE *lostfile = fopen(argv[1], "r");
    if (lostfile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // find first JPEG
        BYTE buffer[512]; // make an array called buffer that is 512 bytes large, this will hold each block as we examine it
        int open = 0; //open JPEG indicator, 0 is closed, 1 is open
        int counter = 0; //counter for filename
        FILE *foundfile; //need to name this outside all the loops since they all use it

    while (fread(buffer, 1, 512, lostfile) == 512) //end of file sequence will be less than 512B, so when we fild a block that is not 512B, exit the while condition and return 0 for finished
    {
        if (open == 1)
        {
            if  (buffer[0] == 0xff &&
                buffer[1] == 0xd8 &&
                buffer[2] == 0xff &&
                (buffer[3] & 0xf0) == 0xe0) //if there's a file open and the new JPEG seq appears, means we reached next photo on card
            {
                fclose (foundfile); //close last photo file
                counter++; //change counter so file name will be different for this photo
                char filename[8]; //char array to store resultant string from sprintf
                sprintf(filename, "%03i.jpg", counter); //using this makes filename change so we can use constant pointer
                foundfile = fopen(filename, "w");
                if (foundfile != NULL)
                {
                    fwrite (buffer, 512, 1, foundfile); //write the block to the new file
                }
            }
            else
            {
                fwrite (buffer, 512, 1, foundfile); //means this block is part of photo file that's already been created and opened, so just write the block to build the photo
            }
        }

        if (open == 0)
        {
            if (buffer[0] == 0xff &&
                buffer[1] == 0xd8 &&
                buffer[2] == 0xff &&
                (buffer[3] & 0xf0) == 0xe0) //if JPEG signature: this is the first photo after the junk blocks
            {
                open = 1; //change open counter so we don't come back to this loop, since we are done with junk blocks
                char filename[8]; //char array to store resultant string from sprintf
                sprintf(filename, "%03i.jpg", counter); //using this makes filename change so we can use constant pointer
                foundfile = fopen(filename, "w");
                if (foundfile != NULL)
                {
                    fwrite (buffer, 512, 1, foundfile); //write the block to the new file
                }
            }
            else
            {
                continue; //junk block, move to next one
            }
        }
    }
    fclose (lostfile);
    fclose (foundfile);
    return 0;
}

// Testing corectness (check50 results): 
// :) recover.c exists.
// :) recover.c compiles.
// :) handles lack of forensic image
// :) recovers 000.jpg correctly
// :) recovers middle images correctly
// :) recovers 015.jpg correctly
