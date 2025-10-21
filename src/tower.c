#include <stdio.h>
#include "tower.h"
#include "pathfinding.h"
#include "game.h"

int isValidCoordinate(int x, int y) {
    return 0;
}

int isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

void placeTower(void) {
    if (playerMoney < 100) {
        printf("Not Enough Money");
        return;
    }
    char coord[4];
    int x, y;
    int validInput = 0;

    while (!validInput) {
        printf("Enter coordinates (e.g. a1, d5): ");
        scanf("%3s", coord);

        /*Convert first letter to lowercase if needed*/
        if (coord[0] >= 'A' && coord[0] <= 'Z')
            coord[0] = coord[0] + 32;

        /*Basic format check*/
        if (!isLetter(coord[0]) || !isDigit(coord[1])) {
            printf("Invalid Input\n");
            continue;
        }

        /*Convert to zero-indexed coordinates*/
        y = coord[0] - 'a';
        sscanf(coord + 1, "%d", &x);
        x--;

        /*Bounds check*/
        if (x < 0 || x >= GRID_X || y < 0 || y >= GRID_Y) {
            printf("Out of bounds\n");
            continue;
        }

        /*Check for existing tower*/
        if (gameBoard[y][x] == '#') {
            printf("There is already a Tower there\n");
            continue;
        }

        /*Place tower temporarily*/
        gameBoard[y][x] = '#';

        /*Check for path to crystal*/
        if (!findPath()) {
            gameBoard[y][x] = '.';
            printf("There has to be a valid path to the crystal\n");
            continue;
        }

        printf("Tower placed at %c%d\n", 'a' + x, y + 1);
        validInput = 1;
    }
    playerMoney -= 100;
}
