// Problem Set 4: Resize. concepts demonstrated: control flow & looping
//
// This is my implementation of Resize, a program that resizes BMPs.
//
// resize.c and all content from CS50 is Copyright © 2015 – 2016, David J. Malan of Harvard University
// This course's content is licensed by David J. Malan of Harvard University under a Creative Commons Attribution-Noncommercial-Share
// Alike 3.0 Unported License, http://creativecommons.org/licenses/by-nc-sa/3.0/
//
// Specification: Implement a program called resize that resizes (i.e., enlarges) 24-bit uncompressed BMPs by a factor of n.
// Your program should accept exactly three command-line arguments, whereby
// the first (n) must be a positive integer less than or equal to 100,
// the second must be the name of a BMP to be resized, and
// the third must be the name of the resized version to be written.
// If your program is not executed with such, it should remind the user of correct usage, and main should return 1.
//
// Usage: $ ./resize int infile.bmp outfile.bmp

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "must include resize factor, infile, and outfile in command line\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 1 || n > 100)
    {
        fprintf(stderr, "resize factor must be between 1 and 100\n");
        return 1;
    }

    // remember filenames
    char *origstring = argv[2];
    char *amendedstring = argv[3];

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

     // copying these orig values into diff ints, to save for later
    int origPadding =  (4 - (bi.biWidth * 3) % 4) % 4;
    int origHeight = bi.biHeight;
    int origWidth = bi.biWidth;
    //update relevant header fields with new size
    int newWidth = bi.biWidth*n;
    int newHeight = bi.biHeight*n;
    bi.biWidth = newWidth;
    bi.biHeight = newHeight;
    int newPadding =  (4 - (newWidth * 3) % 4) % 4;
    int newSize = ((newWidth * 3) + newPadding)*abs(newHeight);
    bi.biSizeImage = newSize;
    bf.bfSize = newSize + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, amendedfile);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, amendedfile);



    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(origHeight); i < biHeight; i++)
    {
        for (int l = 1; l <= n - 1; l++) //start of vertical scale, copy the line n-1 times
        {
                // iterate over pixels in scanline
                for (int j = 0; j < origWidth; j++)
                {
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, origfile);

                    // write RGB triple to outfile, horizontal scale by n
                    for (int k = 1; k <=n; k++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, amendedfile);
                    }

                }

                // skip over padding, if any
                fseek(origfile, origPadding, SEEK_CUR);

                // then add it back
                for (int k = 0; k < newPadding; k++)
                {
                    fputc(0x00, amendedfile);
                }

            fseek(origfile, -1 * ((abs(origWidth) * 3) + origPadding), SEEK_CUR); //move cursor back to start of line to repeat vertical scale
       }
                   // need one more run through line copy to complete vertical scale, so redo operations above without moving cursor back to start after.
                        for (int j = 0; j < origWidth; j++)
                        {
                            RGBTRIPLE triple;

                            // read RGB triple from infile
                            fread(&triple, sizeof(RGBTRIPLE), 1, origfile);

                            // write RGB triple to outfile, horizontal scale by n
                            for (int k = 1; k <=n; k++)
                            {
                                fwrite(&triple, sizeof(RGBTRIPLE), 1, amendedfile);
                            }
                        }

                        // skip over padding, if any
                        fseek(origfile, origPadding, SEEK_CUR);

                        // then add it back
                        for (int k = 0; k < newPadding; k++)
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

// Testing corectness (check50 results):
// :) resize.c and bmp.h exist.
// :) resize.c compiles.
// :) doesn't resize 3x3-pixel BMP when n is 1
// :) resizes 3x3-pixel BMP to 6x6 correctly when n is 2
// :) resizes 3x3-pixel BMP to 9x9 correctly when n is 3
// :) resizes 3x3-pixel BMP to 12x12 correctly when n is 4
// :) resizes 3x3-pixel BMP to 15x15 correctly when n is 5
// :) resizes 6x6-pixel BMP to 12x12 correctly when n is 2
// :) resizes 9x9-pixel BMP to 18x18 correctly when n is 2
// :) resizes 6x6-pixel BMP to 18x18 correctly when n is 3
