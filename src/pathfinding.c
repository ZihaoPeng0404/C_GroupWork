#include <stdio.h>  /* printf */
#include "pathfinding.h"
#include "game.h"

/* Heuristic map for A* pathfinding (Manhattan distance to goal) */
int heuristicMap[GRID_Y][GRID_X] = {
    {4, 5, 6, 7, 8, 9, 10, 11, 12},
    {3, 4, 5, 6, 7, 8, 9, 10, 11},
    {2, 3, 4, 5, 6, 7, 8, 9, 10},
    {1, 2, 3, 4, 5, 6, 7, 8, 9},
    {2, 3, 4, 5, 6, 7, 8, 9, 10},
    {3, 4, 5, 6, 7, 8, 9, 10, 11},
    {4, 5, 6, 7, 8, 9, 10, 11, 12}
};

/* Stores parent nodes for path reconstruction */
Node_t cameFrom[GRID_Y][GRID_X];

/*
 * Prints a node's coordinates and pathfinding values.
 * 
 * Input: node - Node_t to print
 * Output: Prints to stdout
 */
void printNode(Node_t node) {
    printf("x:%d y:%d g:%d h:%d f:%d\n", node.x, node.y, node.g, node.h, node.f);
}

/*
 * Swaps two nodes.
 * 
 * Input: a - pointer to first node
 *        b - pointer to second node
 * Output: Swaps values
 */
void swap(Node_t *a, Node_t *b) {
    Node_t temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * Maintains heap property for priority queue by moving element up.
 * 
 * Input: pq - pointer to priority queue
 *        index - index of element to heapify
 * Output: Modifies pq
 */
void heapifyUp(PriorityQueue_t *pq, int index) {
    if (index == 0) {
        return;
    }
    
    if (pq->nodes[index - 1].f > pq->nodes[index].f) {
        swap(&pq->nodes[index - 1], &pq->nodes[index]);
        heapifyUp(pq, index - 1);
    }
}

/*
 * Adds a new node to the priority queue.
 * 
 * Input: pq - pointer to priority queue
 *        newNode - node to add
 * Output: Modifies pq
 */
void addElement(PriorityQueue_t *pq, Node_t newNode) {
    pq->nodes[pq->size] = newNode;
    heapifyUp(pq, pq->size);
    pq->size++;
}

/*
 * Removes and returns the top priority node from queue.
 * 
 * Input: pq - pointer to priority queue
 * Output: Returns Node_t with lowest f value
 */
Node_t pop(PriorityQueue_t *pq) {
    Node_t poppedNode = pq->nodes[0];
    int index;
    
    for (index = 0; index < pq->size - 1; index++) {
        pq->nodes[index] = pq->nodes[index + 1];
    }

    pq->size--;
    return poppedNode;
}

/*
 * Adds surrounding tiles to priority queue for pathfinding.
 * Explores 4-directional neighbors of current node.
 * 
 * Input: pq - pointer to priority queue
 *        visited - 2D array tracking visited nodes
 *        current - current node being explored
 *        gameBoard - read-only board state
 * Output: Modifies pq and cameFrom
 */
void addSurroundingTiles(PriorityQueue_t *pq, int visited[GRID_Y][GRID_X], 
                         Node_t current, const char gameBoard[GRID_Y][GRID_X]) {
    int directions[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    int directionIndex;
    
    for (directionIndex = 0; directionIndex < 4; directionIndex++) {
        int nextColumn = current.x + directions[directionIndex][0];
        int nextRow = current.y + directions[directionIndex][1];

        /* Bounds check */
        if (nextColumn < 0 || nextColumn >= GRID_X || 
            nextRow < 0 || nextRow >= GRID_Y) {
            continue;
        }
        
        /* Skip if already visited */
        if (visited[nextRow][nextColumn]) {
            continue;
        }
        
        /* Skip if blocked by tower */
        if (gameBoard[nextRow][nextColumn] == TOWER_CHAR) {
            continue;
        }
        
        /* Create neighbor node */
        Node_t neighbour;
        neighbour.x = nextColumn;
        neighbour.y = nextRow;
        neighbour.g = current.g + 1;
        neighbour.h = heuristicMap[nextRow][nextColumn];
        neighbour.f = neighbour.g + neighbour.h;
        neighbour.parentX = current.x;
        neighbour.parentY = current.y;
        
        cameFrom[neighbour.y][neighbour.x] = current;
        addElement(pq, neighbour);
    }
}

/*
 * Finds a path from start portal to goal using A* algorithm.
 * 
 * Input: gameBoard - read-only board state
 * Output: Returns 1 if path found, 0 otherwise
 */
int findPath(const char gameBoard[GRID_Y][GRID_X]) {
    PriorityQueue_t pq = {{{0}}, 0};
    int visited[GRID_Y][GRID_X] = {0};
    
    /* Add start node */
    addElement(&pq, (Node_t){START_X, START_Y, 0, heuristicMap[START_Y][START_X], heuristicMap[START_Y][START_X], 0, 0});
    
    while (pq.size > 0) {
        Node_t current = pop(&pq);

        #ifdef DEBUG
            printNode(current);
        #endif

        if (visited[current.y][current.x]) {
            continue;
        }

        visited[current.y][current.x] = 1;

        /* Check if reached goal */
        if (current.x == GOAL_X && current.y == GOAL_Y) {
            #ifdef DEBUG
                printf("path found\n");
            #endif
            return 1;
        }

        addSurroundingTiles(&pq, visited, current, gameBoard);
    }
    
    #ifdef DEBUG
        printf("No path found\n");
    #endif
    return 0;
}

/*
 * Gets the parent node for path reconstruction.
 * 
 * Input: columnPos - x coordinate
 *        rowPos - y coordinate
 * Output: Returns parent Node_t, or invalid node if out of bounds
 */
Node_t getParentNode(int columnPos, int rowPos) {
    if (columnPos < 0 || columnPos >= GRID_X || rowPos < 0 || rowPos >= GRID_Y) {
        return (Node_t){-1, -1, 0, 0, 0, -1, -1};
    }
    return cameFrom[rowPos][columnPos];
}

/*
 * Gets the goal node for pathfinding.
 * 
 * Input: None
 * Output: Returns goal Node_t
 */
Node_t getGoalNode(void) {
    return (Node_t){GOAL_X, GOAL_Y, 0, 0, 0, -1, -1};
}
