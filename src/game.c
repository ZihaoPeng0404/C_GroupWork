#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "board.h"
#include "tower.h"
#include "wave.h"
#include "save_load.h"
#include "pathfinding.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char gameBoard[GRID_Y][GRID_X];
int crystalHealth = 100;
int waveCount = 1;
int playerMoney = 200;

void initGame(void) {
    resetBoard();
}

void mainMenu(void) {
    int choice;
    int gameLost = 0;
    while (gameLost == 0) {
        drawBoard();
        printf("\n1 - Place a new tower (100$)\n");
        printf("2 - Start next wave\n");
        printf("3 - Save Game\n");
        printf("4 - Load Game\n");
        #ifdef DEBUG
            printf(ANSI_COLOR_RED);
            printf("5 - Test Pathfiding\n");
            printf("6 - Test Enemies\n");
            printf(ANSI_COLOR_RESET);
        #endif
        printf("Choice: ");
        scanf("%d", &choice);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        switch (choice) {
            case 1:
                placeTower();
                break;
            case 2:
                runWave();
                if (crystalHealth <= 0) {
                    gameLost = 1;
                }
                break;
            case 3:
                saveGame();
                break;
            case 4:
                if (loadGameInteractive()) {
                    printf("Game state restored!\n");
                }
                break;
            #ifdef DEBUG
                case 5:
                    findPath();
                    break;
                case 6:
                    runWave();
                    break;
            #endif
            default:
                printf("Invalid choice\n");
        }
        
        /* Check if player won */
        if (waveCount > 10) {
            printf("\n=== CONGRATULATIONS! ===\n");
            printf("You successfully defended the crystal through all 10 waves!\n");
            printf("Final Score - Crystal Health: %d, Money: %d\n", crystalHealth, playerMoney);
            gameLost = 1;
        }
    }
    
    if (crystalHealth <= 0) {
        printf("\n=== GAME OVER ===\n");
        printf("The crystal has been destroyed!\n");
        printf("You survived %d waves.\n", waveCount - 1);
    }
}

void startNextWave(void) {
    /*runWave();*/
    waveCount++;
}