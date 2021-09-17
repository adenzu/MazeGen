#include "util.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
 * @brief       Returns a random integer in range [min, max)
 * @param   min Lower limit, inclusive
 * @param   max Upper limit, exclusive
 * @return      Random integer in range [min, max)
 */
int RandomRange(int min, int max){
    return rand() % (max - min) + min;
}


/**
 * @brief           Creates an array of integers
 * @param   size    Size of the array
 * @return          Pointer to the created array
 */
int * CreateIntArray(int size){
    int * array = (int *) calloc(size, sizeof(int));
    return array;
}


/**
 * @brief           Creates a matrix of integers
 * @param   width   Width of the matrix
 * @param   height  Height of the matrix
 * @return          Pointer to the created matrix
 */
int ** CreateIntMatrix(int width, int height){
    int ** matrix = (int **) calloc(height, sizeof(int *));

    for(int i = 0; i < height; ++i){
        matrix[i] = CreateIntArray(width);
    }

    return matrix;
}


/**
 * @brief           Fills given integer array with given value
 * @param   arr     Pointer to the array to fill
 * @param   size    Size of the array
 * @param   value   Value to fill with
 */
void FillIntArray(int * arr, int size, int value){
    while(size--){
        arr[size] = value;
    }
}


/**
 * @brief           Fills given integer matrix with given value
 * @param   matrix  Pointer to the matrix to fill
 * @param   width   Width of the matrix
 * @param   height  Height of the matrix
 * @param   value   Value to fill with
 */
void FillIntMatrix(int ** matrix, int width, int height, int value){
    while(height--){
        FillIntArray(matrix[height], width, value);
    }
}


/**
 * @brief           Fills given uint8_t array with given value
 * @param   arr     Pointer to the array to fill
 * @param   size    Size of the array
 * @param   value   Value to fill with
 */
void FillU8Array(uint8_t * arr, int size, uint8_t value){
    while(size--){
        arr[size] = value;
    }
}


/**
 * @brief               Returns the differential ceiling of the given value by the given difference
 * @param   difference  Common difference
 * @param   value       Value to get the ceiling of
 * @return              Differential ceiling of the given value
 * 
 * @example
 * DifferentialCeil(6, 9) = 12
 * DifferentialCeil(64, 81) = 128
 */
int DifferentialCeil(int difference, int value){
    return (int) ceilf((float) value / difference) * difference;
}