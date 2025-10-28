#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "game.h"

/* Node structure for A* pathfinding */
typedef struct {
    int x;
    int y;
    int g;          /* Cost from start */
    int h;          /* Heuristic to goal */
    int f;          /* Total cost (g + h) */
    int parentX;
    int parentY;
} Node_t;

/* Priority queue for pathfinding */
typedef struct {
    Node_t nodes[MAX_QUEUE_SIZE];
    int size;
} PriorityQueue_t;

/* Function declarations */
int findPath(const char gameBoard[GRID_Y][GRID_X]);
Node_t getParentNode(int x, int y);
Node_t getGoalNode(void);

#endif
