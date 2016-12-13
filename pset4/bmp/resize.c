/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, then enlarges the BMP by
 * a factor of n.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // copy BMP headers for editing
    BITMAPFILEHEADER newbf;
    BITMAPINFOHEADER newbi;
    newbf = bf;
    newbi = bi;
    
    // resize width and height
    newbi.biWidth = n * bi.biWidth;
    newbi.biHeight = n * bi.biHeight;
    
    // new padding, bytes
    int newpad = (4 - (newbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // resize image and file
    newbi.biSizeImage = (newbi.biWidth * sizeof(RGBTRIPLE) + newpad)
                        * abs(newbi.biHeight);
    newbf.bfSize = newbi.biSizeImage + 54;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&newbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&newbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines, bytes
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // for each infile scanline we'll have n outfile scanlines
        for (int vert = 0; vert < n; vert++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
            
                // read in RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
                // write out that triple n times
                for (int horiz = 0; horiz < n; horiz++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            
            // add new padding, if needed    
            }
            for (int k = 0; k < newpad; k++)
            {
                fputc(0x00, outptr);
            }
            
            // move back to beginning of infile scanline    
            fseek(inptr, -(bi.biWidth * 3), SEEK_CUR);
        }
        fseek(inptr, (padding + (bi.biWidth * 3)), SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
