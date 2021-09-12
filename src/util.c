#include "util.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int Sum(int * arr, int size){
    int sum = 0;
    
    while(size--){
        sum += arr[size];
    }

    return sum;
}

int RandomRange(int min, int max){
    return rand() % (max - min) + min;
}

int RandomIndex(int * odds, int size){
    int oddSum = Sum(odds, size);
    int random = RandomRange(0, oddSum);

    while(size--){
        if(random < odds[size]){
            return size;
        }
        random -= odds[size];
    }
}

int * CreateIntArray(int size){
    int * array = (int *) calloc(size, sizeof(int));
    return array;
}

int ** CreateIntMatrix(int width, int height){
    int ** matrix = (int **) calloc(height, sizeof(int *));

    for(int i = 0; i < height; ++i){
        matrix[i] = CreateIntArray(width);
    }

    return matrix;
}

void FillIntArray(int * arr, int size, int value){
    while(size--){
        arr[size] = value;
    }
}

void FillIntMatrix(int ** matrix, int width, int height, int value){
    while(height--){
        FillIntArray(matrix[height], width, value);
    }
}

void PrintIntArray(int * arr, int size){
    for(int i = 0; i < size; ++i){
        printf("%*c", 5 - printf("%d", arr[i]), ' ');
    }
}

void PrintIntMatrix(int ** matrix, int width, int height){
    for(int i = 0; i < height; ++i){
        PrintIntArray(matrix[i], width);
        printf("\n");
    }
}

void FillU8Array(uint8_t * arr, int size, uint8_t value){
    while(size--){
        arr[size] = value;
    }
}

int DifferentialCeil(int difference, int value){
    return (int) ceilf((float) value / difference) * difference;
}






