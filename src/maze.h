#ifndef MAZE_H
#define MAZE_H

typedef enum Direction {
    RIGHT = 0b0001,
    UP    = 0b0010,
    DOWN  = 0b0100,
    LEFT  = 0b1000
} Direction;

typedef struct Maze {
    int ** matrix;
    int width, height;
} Maze;

Maze * CreateMaze(int width, int height);
int * GetMazeTile(Maze * maze, int x, int y);
void ResetMaze(Maze * maze);
void FreeMaze(Maze * maze);
void GenerateMaze(Maze * maze, unsigned seed);
void SaveMaze(Maze * maze, char * filename);

#endif//MAZE_H