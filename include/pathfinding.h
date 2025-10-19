#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "game.h"

#define MAX 100

typedef struct
{
    int x;
    int y;
    int g;
    int h;
    int f;
    int parentX;
    int parentY;
} Node;

typedef struct 
{
    Node Nodes[MAX];
    int size;
} PriorityQueue;

int findPath(void);
Node getParentNode(int x, int y);
Node getGoalNode(void);
#endif
