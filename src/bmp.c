#include "bmp.h"
#include "util.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define BMP_HEADER_SIZE 14
#define DIB_HEADER_SIZE 40
#define COLOR_COUNT 2

/**
 * @brief           Creates a BMP image
 * @param   width   Width of the BMP image in pixels
 * @param   height  Height of the BMP image in pixels
 * @return          Pointer to the created BMP image
 */
BMP * CreateBMP(int width, int height){
    BMP * bmp = (BMP *) malloc(sizeof(BMP));
    
    bmp->width = width;
    bmp->height = height;
    
    // Number of bytes of pixel rows has to be divisible by 4 for padding reasons set by BMP file format
    bmp->dataRowSize = DifferentialCeil(4, ceilf(bmp->width / 8.0f));

    // Number of total bytes of the data
    bmp->dataSize = BMP_HEADER_SIZE + DIB_HEADER_SIZE + 4 * COLOR_COUNT + bmp->dataRowSize * bmp->height;
    bmp->data = (uint8_t *) calloc(bmp->dataSize, sizeof(uint8_t));

    // set up the BMP image's data
    FillU8Array(bmp->data, bmp->dataSize, 0);
    SetBMPHeader(bmp);
    SetDIBHeader(bmp);
    
    return bmp;
}


/**
 * @brief       Sets up the BMP Header
 * @param   bmp Pointer to the BMP image to be set
 */
void SetBMPHeader(BMP * bmp){
    // BMP file specifier
    bmp->data[0] = 'B';
    bmp->data[1] = 'M';

    // Start index of the pixel array
    bmp->data[10] = BMP_HEADER_SIZE + DIB_HEADER_SIZE + 4 * COLOR_COUNT;
}


/**
 * @brief       Sets up the DIB header
 * @param   bmp Pointer to the BMP image to be set
 */
void SetDIBHeader(BMP * bmp){
    bmp->data[14] = DIB_HEADER_SIZE;                    // Size of the DIB header
    bmp->data[26] = 1;                                  // 1 plane
    bmp->data[28] = 1;                                  // 1 bit / pixel
    bmp->data[34] = bmp->dataRowSize * bmp->height;   // Size of the pixel array
    bmp->data[46] = COLOR_COUNT;                        // Number of colors
    bmp->data[50] = COLOR_COUNT;                        // Number of important colors

    // black
    bmp->data[54] = 0;
    bmp->data[55] = 0;
    bmp->data[56] = 0;
    bmp->data[57] = 0;

    // white
    bmp->data[58] = 0xFF;   
    bmp->data[59] = 0xFF;
    bmp->data[60] = 0xFF;
    bmp->data[61] = 0;

    // set BMP image width
    bmp->data[18] = bmp->width & 0xFF;
    bmp->data[19] = (bmp->width >> 8) & 0xFF;
    
    // set BMP image height
    bmp->data[22] = bmp->height & 0xFF;
    bmp->data[23] = (bmp->height >> 8) & 0xFF;
}


/**
 * @brief           Sets the values of the BMP image's pixels to given pixels' 
 * @param   bmp     Pointer to the BMP image whose pixels will be set
 * @param   pixels  Pixels to be set 
 */
void SetPixels(BMP * bmp, const int * pixels){
    int headerOffset = BMP_HEADER_SIZE + DIB_HEADER_SIZE + 4 * COLOR_COUNT;

    for(int y = 0; y < bmp->height; ++y){
        int rowOffset  = bmp->width * y;
        int dataOffset = headerOffset + bmp->dataRowSize * y;

        for(int x = 0; x < bmp->width; ++x){
            bmp->data[dataOffset + x / 8] <<= 1;
            bmp->data[dataOffset + x / 8] |= pixels[rowOffset + x];
        }
    }
}


/**
 * @brief               Saves BMP image by the given file name
 * @param   bmp         BMP image to save
 * @param   filename    Name of the file to save  
 */
void SaveBMP(BMP * bmp, const char * filename){
    FILE * fp = fopen(filename, "wb");
    fwrite(bmp->data, sizeof(uint8_t), bmp->dataSize, fp);
    fclose(fp);
}


/**
 * @brief       Frees the BMP image
 * @param   bmp BMP image to free
 */
void FreeBMP(BMP * bmp){
    free(bmp->data);
    free(bmp);
}