#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "board.h"
#include "tower.h"
#include "wave.h"
#include "save_load.h"

char gameBoard[GRID_Y][GRID_X];
int crystalHealth = 100;
int waveCount = 1;
int playerMoney = 200;

void initGame(void) {
    resetBoard();
}

void mainMenu(void) {
    int choice;
    while (1) {
        drawBoard();
        printf("\n1 - Place a new tower (100$)\n");
        printf("2 - Start next wave\n");
        printf("3 - Save Game\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("place tower");
                /*placeTower();*/
                break;
            case 2:
                printf("startNextWave");
                break;
            case 3:
                printf("saveGame");
                break;
            default:
                printf("Invalid choice\n");
        }
    }
}

void startNextWave(void) {
    /*runWave();*/
    waveCount++;
}
