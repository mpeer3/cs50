// Resizes a BMP file...By Michael Peer 2018

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize factor infile outfile\n");
        return 1;
    }
    float factor = atof(argv[1]);

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
    bool shrink = false;
    int f = 0;

    if (factor >= 1)
    {
        f = roundf(factor);
        bi.biWidth = bi.biWidth * f;
        bi.biHeight = bi.biHeight * f;
    }
    else
    {
        f = roundf(1 / factor);
        shrink = true;
        bi.biWidth = bi.biWidth / f;
        bi.biHeight = bi.biHeight / f;
    }

    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding2 = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = abs(bi.biHeight) * (bi.biWidth * sizeof(RGBTRIPLE) + padding2);
    bf.bfSize = bi.biSizeImage + 54;
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    if (shrink == true)
    {
        for (int i = 0, biHeight = abs(height); i < biHeight; i++)
        {
            if ((i % f == 0) || (i == 0))
            {
                for (int j = 0; j < width; j++)
                {
                    RGBTRIPLE triple;
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    if ((j % f == 0) || (j == 0))
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }

                }
                fseek(inptr, padding, SEEK_CUR);
                for (int k = 0; k < padding2; k++)
                {
                    fputc(0x00, outptr);

                }
            }
            else
            {
                int shift = width * sizeof(RGBTRIPLE) + padding;
                fseek(inptr, shift, SEEK_CUR);
            }
        }

    }
    else
    {
        for (int i = 0, biHeight = abs(height); i < biHeight; i++)
        {
            for (int ctt = 0; ctt < f; ctt++)
            {
                for (int j = 0; j < width; j++)
                {
                    RGBTRIPLE triple;
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    for (int ct = 0; ct < f; ct++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                    }

                }
                fseek(inptr, padding, SEEK_CUR);
                for (int k = 0; k < padding2; k++)
                {
                    fputc(0x00, outptr);

                }
                if (ctt < f - 1)
                {
                    int shift = width * sizeof(RGBTRIPLE) + padding;
                    fseek(inptr, -shift, SEEK_CUR);

                }

            }

        }
        fclose(inptr);
        fclose(outptr);
        return 0;

    }

}
