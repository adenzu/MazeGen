#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

int RandomRange(int min, int max);
int * CreateIntArray(int size);
int ** CreateIntMatrix(int width, int height);
void FillIntArray(int * arr, int size, int value);
void FillIntMatrix(int ** matrix, int width, int height, int value);
void FillU8Array(uint8_t * arr, int size, uint8_t value);
int DifferentialCeil(int difference, int value);

#endif//UTIL_H