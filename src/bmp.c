#include "bmp.h"
#include "util.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define BMP_HEADER_SIZE 14
#define DIB_HEADER_SIZE 40
#define COLOR_COUNT 2

BMP * CreateBMP(int width, int height){
    BMP * bmp = (BMP *) malloc(sizeof(BMP));
    
    bmp->width = width;
    bmp->height = height;
    
    bmp->bitmapRowSize = DifferentialCeil(4, ceilf(bmp->width / 8.0f));
    bmp->dataSize = BMP_HEADER_SIZE + DIB_HEADER_SIZE + 4 * COLOR_COUNT + bmp->bitmapRowSize * bmp->height;
    bmp->data = (uint8_t *) calloc(bmp->dataSize, sizeof(uint8_t));

    FillU8Array(bmp->data, bmp->dataSize, 0);
    SetBMPHeader(bmp);
    SetDIBHeader(bmp);
    
    return bmp;
}

void SetBMPHeader(BMP * bmp){
    bmp->data[0] = 'B';
    bmp->data[1] = 'M';
    bmp->data[10] = BMP_HEADER_SIZE + DIB_HEADER_SIZE + 8;
}

void SetDIBHeader(BMP * bmp){
    bmp->data[14] = DIB_HEADER_SIZE;
    bmp->data[26] = 1;  // 1 plane
    bmp->data[28] = 1;  // 1 bit / pixel
    bmp->data[34] = bmp->bitmapRowSize * bmp->height;
    bmp->data[46] = COLOR_COUNT;
    bmp->data[50] = COLOR_COUNT;

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

    bmp->data[18] = bmp->width & 0xFF;
    bmp->data[19] = (bmp->width >> 8) & 0xFF;
    
    bmp->data[22] = bmp->height & 0xFF;
    bmp->data[23] = (bmp->height >> 8) & 0xFF;
}

void SetPixels(BMP * bmp, const int * pixels){
    int headerOffset = BMP_HEADER_SIZE + DIB_HEADER_SIZE + 8;

    for(int y = 0; y < bmp->height; ++y){
        int heightOffset = bmp->width * y;
        int dataOffset = headerOffset + bmp->bitmapRowSize * y;

        for(int x = 0; x < bmp->width; ++x){
            bmp->data[dataOffset + x / 8] <<= 1;
            bmp->data[dataOffset + x / 8] |= pixels[heightOffset + x];
        }
    }
}

void SaveBMP(BMP * bmp, char * filename){
    FILE * fp = fopen(filename, "wb");
    fwrite(bmp->data, sizeof(uint8_t), bmp->dataSize, fp);
    fclose(fp);
}

void FreeBMP(BMP * bmp){
    free(bmp->data);
    free(bmp);
}