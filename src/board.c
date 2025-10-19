#include <stdio.h>
#include "board.h"

void resetBoard(void) {
    int y;
    for (y = 0; y < GRID_Y; y++) {
        int x;
        for (x = 0; x < GRID_X; x++) {
            gameBoard[y][x] = '.';
        }
    }
}

void drawBoard(void) {
    printf("\nCrystal Health: %d/100   Wave: %d/10   Money: %d$\n", crystalHealth, waveCount, playerMoney);

    printf("#   #   ");
    int x;
    for (x = 1; x <= GRID_X; x++) printf("%d   ", x);
    printf("#   #");
    printf("\n");
    for (x = 1; x <= GRID_X + 4; x++) printf("#   ");
    printf("\n");

    int y;
    for (y = 0; y < GRID_Y; y++) {
        /*Handle portal placement*/
        if (y == 3) {
            printf("%c   @   ", 'A' + y);
        }
        else {
            printf("%c   #   ", 'A' + y);
        }
        
        int x;
        for (x = 0; x < GRID_X; x++) {
            printf("%c   ", gameBoard[y][x]);
        }

        if (y == 3) {
            printf("O   #");
        }
        else {
            printf("#   #");
        }
        printf("\n");
    }
    for (x = 1; x <= GRID_X + 4; x++) printf("#   ");
    printf("\n");
}

int inBoundsCheck(int x, int y) {
    if (x < 0 || x > GRID_X || y < 0 || y > GRID_Y) {
        return 0;
    }
    return 1;
} 
void checkSurroundingTiles(int x, int y) {

}
