// Problem Set 4: Whodunit. concepts demonstrated: lists & arrays, create & call functions.
//
// This is my implementation of Whodunit, a program that reveals a hidden message in a BMP. We have a clue: a BMP with a lot of red 
// "noise", the answer to 'whodunit' is being concealed by the excess red in the BMP's pixels. My program will iterate through the pixels in the BMP and eliminate the red to reveal the hidden message
//
// whodunit.c and all content from CS50 is Copyright © 2015 – 2016, David J. Malan of Harvard University
// This course's content is licensed by David J. Malan of Harvard University under a Creative Commons Attribution-Noncommercial-Share
// Alike 3.0 Unported License, http://creativecommons.org/licenses/by-nc-sa/3.0/
//
// Specification: Implement a program called whodunit that reveals Mr. Boddy’s drawing in such a way that you can recognize whodunit.
// Your program should accept exactly two command-line arguments: the name of an input file to open for reading followed by the name of 
// an output file to open for writing.
// If your program is executed with fewer or more than two command-line arguments, it should remind the user of correct usage, and main 
// should return 1.
// If the input file cannot be opened for reading, your program should inform the user as much, and main should return 2.
// If the output file cannot be opened for writing, your program should inform the user as much, and main should return 3.
// If the input file is not a 24-bit uncompressed BMP 4.0, your program should inform the user as much, and main should return 4.
// Upon success, main should 0.
//
// Usage: $ ./whodunit inputfile.bmp outputfile.bmp

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        fprintf(stderr, "must include infile and outfile in command line\n");
        return 1;
    }

    // remember filenames
    char *origstring = argv[1];
    char *amendedstring = argv[2];

     // open input file
    FILE *origfile = fopen(origstring, "r");
    if (origfile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", origstring);
        return 2;
    }

    // open output file
    FILE *amendedfile = fopen(amendedstring, "w");
    if (amendedfile == NULL)
    {
        fclose(origfile);
        fprintf(stderr, "Could not create %s.\n", amendedstring);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, origfile);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, origfile);

     // ensure infile is a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0) //look in the bf and bi structures (created above) at these elements which are defined/labeled by bmp.h
    {
        fclose(amendedfile);
        fclose(origfile);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, amendedfile);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, amendedfile);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, origfile);

            if (triple.rgbtRed == 0xff) //if the pixel's red is set to full value
            {
                //remove red
                triple.rgbtRed = 0x00;
            }

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, amendedfile);
        }

        // skip over padding, if any
        fseek(origfile, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, amendedfile);
        }

    }

    // close infile
    fclose(origfile);

    // close outfile
    fclose(amendedfile);

    // success
    return 0;
}
