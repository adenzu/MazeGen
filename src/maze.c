#include "maze.h"
#include "util.h"
#include "bmp.h"

#include <stdlib.h>
#include <stdio.h>

Maze * CreateMaze(int width, int height){
    Maze * maze = (Maze *) malloc(sizeof(Maze));

    maze->matrix = CreateIntMatrix(width, height);
    maze->width = width;
    maze->height = height;

    ResetMaze(maze);

    return maze;
}

int * GetMazeTile(Maze * maze, int x, int y){
    return &(maze->matrix[y][x]);
}

void ResetMaze(Maze * maze){
    FillIntMatrix(maze->matrix, maze->width, maze->height, 0);
}

void FreeMaze(Maze * maze){
    while(maze->height--){
        free(maze->matrix[maze->height]);
    }
    free(maze->matrix);
    free(maze);
}

void RecursiveMazeGeneration(Maze * maze, int x, int y){
    int * tile = GetMazeTile(maze, x, y);
    int baseMask = 0b10001000 >> RandomRange(0, 4);

    for(int bitIndex = 0; bitIndex < 4; ++bitIndex){
        int mask = baseMask >> bitIndex;
        int nextX = x, nextY = y;
        int direction = (~*tile & 0b1111) & mask;

        switch(direction){
            case RIGHT:
                ++nextX;
                break;
            case UP:
                ++nextY;
                break;
            case DOWN:
                --nextY;
                break;
            case LEFT:
                --nextX;
                break;
            default:
                nextX = -1;
        }

        if(nextX > -1 && nextY > -1 && nextX < maze->width && nextY < maze->height && !*GetMazeTile(maze, nextX, nextY)){
            *tile |= direction;
            *GetMazeTile(maze, nextX, nextY) |= 8 / direction;
            RecursiveMazeGeneration(maze, nextX, nextY);
        }
    }
}

void GenerateMaze(Maze * maze, unsigned seed){
    srand(seed);
    RecursiveMazeGeneration(maze, 0, 0);
    *GetMazeTile(maze, 0, 0) |= LEFT;
    *GetMazeTile(maze, maze->width - 1, maze->height - 1) |= RIGHT;
}

void SaveMaze(Maze * maze, char * filename){
    BMP * bmp = CreateBMP(4 * maze->width, 4 * maze->height);
    int * pixels = (int *) calloc(bmp->width * bmp->height, sizeof(int));

    int white = 1;
    int black = 0;

    for(int y = 0; y < maze->height; ++y) {
        for(int x = 0; x < maze->width; ++x){
            int tile = maze->matrix[y][x];
            int pixelY = 4 * y, pixelX = 4 * x;

            // center
            pixels[(pixelY + 1) * bmp->width + pixelX + 1] = white;
            pixels[(pixelY + 1) * bmp->width + pixelX + 2] = white;
            pixels[(pixelY + 2) * bmp->width + pixelX + 1] = white;
            pixels[(pixelY + 2) * bmp->width + pixelX + 2] = white;
            
            // vertices
            pixels[pixelY * bmp->width + pixelX]           = black;
            pixels[(pixelY + 3) * bmp->width + pixelX]     = black;
            pixels[pixelY * bmp->width + pixelX + 3]       = black;
            pixels[(pixelY + 3) * bmp->width + pixelX + 3] = black;

            // sides
            if(tile & RIGHT){
                pixels[(pixelY + 1) * bmp->width + pixelX + 3] = white;
                pixels[(pixelY + 2) * bmp->width + pixelX + 3] = white;
            }
            else{
                pixels[(pixelY + 1) * bmp->width + pixelX + 3] = black;
                pixels[(pixelY + 2) * bmp->width + pixelX + 3] = black;
            }

            if(tile & UP){
                pixels[(pixelY + 3) * bmp->width + pixelX + 1] = white;
                pixels[(pixelY + 3) * bmp->width + pixelX + 2] = white;
            }
            else{
                pixels[(pixelY + 3) * bmp->width + pixelX + 1] = black;
                pixels[(pixelY + 3) * bmp->width + pixelX + 2] = black;
            }

            if(tile & DOWN){
                pixels[pixelY * bmp->width + pixelX + 1] = white;
                pixels[pixelY * bmp->width + pixelX + 2] = white;
            }
            else{
                pixels[pixelY * bmp->width + pixelX + 1] = black;
                pixels[pixelY * bmp->width + pixelX + 2] = black;
            }

            if(tile & LEFT){
                pixels[(pixelY + 1) * bmp->width + pixelX] = white;
                pixels[(pixelY + 2) * bmp->width + pixelX] = white;
            }
            else{
                pixels[(pixelY + 1) * bmp->width + pixelX] = black;
                pixels[(pixelY + 2) * bmp->width + pixelX] = black;
            }
        }
    }

    SetPixels(bmp, pixels);
    SaveBMP(bmp, filename);
    FreeBMP(bmp);
    free(pixels);
}