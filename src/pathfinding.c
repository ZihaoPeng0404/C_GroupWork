#include <stdio.h>
#include "pathfinding.h"


int heuristicMap[7][9] = {
    {4, 5, 6, 7, 8, 9, 10, 11, 12},
    {3, 4, 5, 6, 7, 8, 9, 10, 11},
    {2, 3, 4, 5, 6, 7, 8, 9, 10},
    {1, 2, 3, 4, 5, 6, 7, 8, 9},
    {2, 3, 4, 5, 6, 7, 8, 9, 10},
    {3, 4, 5, 6, 7, 8, 9, 10, 11},
    {4, 5, 6, 7, 8, 9, 10, 11, 12}
};

Node cameFrom[GRID_Y][GRID_X];



void printNode(Node node) {
    printf("x:%d y:%d g:%d h:%d f:%d\n", node.x, node.y, node.g, node.h, node.f);
}
void swap(Node* a, Node* b){
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue* pq, int index) {
    if (index == 0) {return;}
    if (pq->Nodes[index - 1].f > pq->Nodes[index].f) {
        swap(&pq->Nodes[index - 1], &pq->Nodes[index]);
        heapifyUp(pq, index - 1);
    }
}

void addElement(PriorityQueue* pq, Node newNode) {
    pq->Nodes[pq->size] = newNode;
    heapifyUp(pq, pq->size);
    pq->size++;
}

Node pop(PriorityQueue* pq) {
    Node poppedNode = pq->Nodes[0];
    int i;
    for (i = 0; i < pq->size - 1; i++) {
        pq->Nodes[i] = pq->Nodes[i + 1];
    }

    pq->size--;
    return poppedNode;
}

void addSurroundingTiles(PriorityQueue *pq, int visited[7][9], Node current) {
    int directions[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    int i;
    for (i = 0; i < 4; i++) {
        int nx = current.x + directions[i][0];
        int ny = current.y + directions[i][1];

        if (nx < 0 || nx >= GRID_X || ny < 0 || ny >= GRID_Y)
            continue;
        if (visited[ny][nx])
            continue;
        if (gameBoard[ny][nx] == '#')
            continue;
        Node neighbour;
        neighbour.x = nx;
        neighbour.y = ny;
        neighbour.g = current.g + 1;
        neighbour.h = heuristicMap[ny][nx];
        neighbour.f = neighbour.g + neighbour.h;
        neighbour.parentX = current.x;
        neighbour.parentY = current.y;
        cameFrom[neighbour.y][neighbour.x] = current;
        addElement(pq, neighbour);
    }
}

int findPath(void) {
    PriorityQueue pq = {{{0}}, 0};

    int visited[7][9] = {0};
    addElement(&pq, (Node){9, 3, 0, 10, 10});
    while (pq.size > 0) {
        Node current = pop(&pq);

        #ifdef DEBUG
            printNode(current);
        #endif

        if (visited[current.y][current.x])
            continue;

        visited[current.y][current.x] = 1;

        if (current.x == 0 && current.y == 3) {
            #ifdef DEBUG
                printf("path found");
            #endif
            return 1;
        }

        addSurroundingTiles(&pq, visited, current);
    }
    #ifdef DEBUG
        printf("No path found");
    #endif
    return 0;
}

Node getParentNode(int x, int y) {
    if (x < 0 || x >= GRID_X || y < 0 || y >= GRID_Y) {
        return (Node){-1,-1,0,0,0,-1,-1};
    }
    return cameFrom[y][x];
}

Node getGoalNode() {
    return (Node){0, 3, 0, 0, 0, -1, -1};
}
