#include <stdio.h>
#include "pathfinding.h"


#define MAX 100

int heuristicMap[7][9] = {
    {4, 5, 6, 7, 8, 9, 10, 11, 12},
    {3, 4, 5, 6, 7, 8, 9, 10, 11},
    {2, 3, 4, 5, 6, 7, 8, 9, 10},
    {1, 2, 3, 4, 5, 6, 7, 8, 9},
    {2, 3, 4, 5, 6, 7, 8, 9, 10},
    {3, 4, 5, 6, 7, 8, 9, 10, 11},
    {4, 5, 6, 7, 8, 9, 10, 11, 12}
};

typedef struct
{
    int x;
    int y;
    int distance;
} Node;

typedef struct 
{
    Node Nodes[MAX];
    int size;
} PriorityQueue;

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}



int findPath(void) {
    /*TODO: implement A* pathfinding here*/
    return 1;
}
