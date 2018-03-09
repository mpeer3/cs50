// Resizes a BMP file...By Michael Peer 2018

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize factor infile outfile\n");
        return 1;
    }
    int factor = atoi(argv[1]);
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
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
    LONG width = bi.biWidth;
    LONG height = bi.biHeight;
    bi.biWidth = bi.biWidth * factor;
    bi.biHeight = bi.biHeight * factor;
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding2 = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = abs(bi.biHeight) * (bi.biWidth * sizeof(RGBTRIPLE) + padding2);
    bf.bfSize = bi.biSizeImage + 54;
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(height); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int ctt = 0; ctt < factor; ctt++)
        {
            for (int j = 0; j < width; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                for (int ct = 0; ct < factor; ct++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                }

            }
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);
            // then add it back (to demonstrate how)
            for (int k = 0; k < padding2; k++)
            {
                fputc(0x00, outptr);

            }
            if (ctt < factor - 1)
            {
                int shift = width * sizeof(RGBTRIPLE) + padding;
                fseek(inptr, -shift, SEEK_CUR);

            }

        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
