#include <stdio.h>
#include "wave.h"
#include "pathfinding.h"
#include "board.h"

int isEnemy(char c) {
    return (c != '.' && c != '#');
}

void damageEnemy(int x, int y) {
    int directions[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    int i;
    for (i = 0; i < 4; i++) {
        if (gameBoard[y][x] == '.')
            continue;

        int nx = x + directions[i][0];
        int ny = y + directions[i][1];

        if (nx < 0 || nx >= GRID_X || ny < 0 || ny >= GRID_Y)
            continue;
        if (gameBoard[ny][nx] == '#')
            gameBoard[y][x] -= 1;
        if (gameBoard[y][x] == '0') {
            playerMoney += 50;
            gameBoard[y][x] = '.';
        }
    }
}

void moveEnemies() {
    Node current = getGoalNode();
    if (isEnemy(gameBoard[current.y][current.x])) {
        crystalHealth -= gameBoard[current.y][current.x] - '0';
        gameBoard[current.y][current.x] = '.';
    }
    while (current.x != 8 || current.y != 3) {
        Node parentNode = getParentNode(current.x, current.y);
        if (isEnemy(gameBoard[parentNode.y][parentNode.x])) {
            damageEnemy(parentNode.x, parentNode.y);
            gameBoard[current.y][current.x] = gameBoard[parentNode.y][parentNode.x];
            gameBoard[parentNode.y][parentNode.x] = '.';
        }
        current = parentNode;
    }
}

int anyEnemiesOnBoard(void) {
    int x, y;
    for (y = 0; y < GRID_Y; y++) {
        for (x = 0; x < GRID_X; x++) {
            if (isEnemy(gameBoard[y][x])) {
                return 1;
            }
        }
    }
    return 0;
}


void runWave(void) {
    findPath();

    int i;
    for (i = 0; i < waveCount; i++)
    {
        moveEnemies();
        gameBoard[3][8] = '0' + waveCount;
        drawBoard();
        int k;
        for (k = 0; k < GAME_DELAY; k++){;}
    }
    while (anyEnemiesOnBoard()) {
        moveEnemies();
        drawBoard();
        int k;
        for (k = 0; k < GAME_DELAY; k++){;}
    }
    waveCount++;
}

