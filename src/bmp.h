#ifndef BMP_H
#define BMP_H

#include <stdint.h>

typedef struct BMP {
    uint8_t * data;
    int dataSize, bitmapRowSize;
    int width, height;
} BMP;

BMP * CreateBMP(int width, int height);
void SetBMPHeader(BMP * bmp);
void SetDIBHeader(BMP * bmp);
void SetPixels(BMP * bmp, const int * pixels);
void SaveBMP(BMP * bmp, char * filename);
void FreeBMP(BMP * bmp);

#endif//BMP_H