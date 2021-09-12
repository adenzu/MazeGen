#include "maze.h"
#include "bmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){
    int mazeWidth, mazeHeight, mazeSeed = time(NULL);
    char * filename = "out.bmp";
    
    switch(argc){
        case 5:
            filename = argv[4];
        case 4:
            mazeSeed = atoi(argv[3]);
        case 3:
            mazeWidth = atoi(argv[1]);
            mazeHeight = atoi(argv[2]);
            break;
        default:
            printf("Usage: %s [width] [height] <seed> <file name>\n", argv[0]);
            return 1;
    }

    Maze * maze = CreateMaze(mazeWidth, mazeHeight);
    
    printf("Generating maze...");
    GenerateMaze(maze, mazeSeed); 
    printf("Done!\n");
    
    printf("Saving maze to '%s'...", filename);
    SaveMaze(maze, filename); 
    printf("Done!\n");
    
    FreeMaze(maze);
    return 0;
}