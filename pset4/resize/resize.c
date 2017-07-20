/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    float size = atof(argv[1]);
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
    //creates a clone of the header so the loop still reads over original width/height.
    BITMAPINFOHEADER bio=bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    //creates the variables used for repeting a pixel/line or jumping a pixel/line
    int f;
    int jump;
    if(size>=1){
        f = size;
        jump = 1;
        bi.biWidth *=f;    
        bi.biHeight *=f;
    }else{
        f = 1;
        jump = 1/size;
        bi.biWidth /=jump;
        bi.biHeight /=jump;
    }
    //creates the padding for the outfile
    int pad = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //sets the headers for the new file
    bi.biSizeImage=((sizeof(RGBTRIPLE)*bi.biWidth)+pad)*abs(bi.biHeight);
    bf.bfSize=bi.biSizeImage+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
    
    // determine padding for scanlines
    int padding = (4 - (bio.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bio.biHeight/jump); i < biHeight; i++)
    {   
        //gets the current position for the pointer
        int startofline = ftell(inptr);
        //repeat lines if necessary
        for(int l=0; l<f;l++){
          // sets the program to read the current position before this loop started
          // so to read the same line as many times as needed
          fseek(inptr,startofline,SEEK_SET);
            // iterate over pixels in scanline
            for (int j = 0; j < bio.biWidth/jump; j++)
            {

                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile f times
                for(int k=0;k<f;k++){
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                //jumps (n) pixels if it's making the image smaller
                for(int lj=1;lj<jump;lj++){
                    fseek(inptr,sizeof(RGBTRIPLE),SEEK_CUR);
                }
            }
            //add the new padding
            for (int k = 0; k < pad; k++)
            {
                fputc(0x00, outptr);
            }

        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
        //jumps (n) next lines if it's making the image smaller
        for(int lj=1;lj<jump;lj++){
            fseek(inptr,sizeof(RGBTRIPLE)*bio.biWidth,SEEK_CUR);
            fseek(inptr, padding, SEEK_CUR);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
