#include <stdio.h>  /* printf, scanf, getchar */
#include <stdlib.h>
#include "game.h"
#include "board.h"
#include "tower.h"
#include "wave.h"
#include "save_load.h"
#include "pathfinding.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*
 * Initializes a new game state with default values.
 * 
 * Input: gameState - pointer to GameState_t to initialize
 * Output: Modifies gameState with initial values
 */
void initGame(GameState_t *gameState) {
    gameState->crystalHealth = INITIAL_CRYSTAL_HEALTH;
    gameState->waveCount = INITIAL_WAVE_COUNT;
    gameState->playerMoney = INITIAL_PLAYER_MONEY;
    resetBoard(gameState->gameBoard);
}

/*
 * Main game menu loop.
 * Handles user input and game flow until game over or win.
 * 
 * Input: gameState - pointer to current game state
 * Output: Modifies gameState throughout gameplay
 */
void mainMenu(GameState_t *gameState) {
    int choice;
    int gameLost = 0;
    
    while (gameLost == 0) {
        drawBoard(gameState);
        printf("\n1 - Place a new tower (%d$)\n", TOWER_COST);
        printf("2 - Start next wave\n");
        printf("3 - Save Game\n");
        printf("4 - Load Game\n");
        #ifdef DEBUG
            printf(ANSI_COLOR_RED);
            printf("5 - Test Pathfinding\n");
            printf("6 - Test Enemies\n");
            printf(ANSI_COLOR_RESET);
        #endif

        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            /* Clear the input buffer */
            int inputChar;
            while ((inputChar = getchar()) != '\n' && inputChar != EOF);
            continue;
        }
        
        switch (choice) {
            case 1:
                placeTower(gameState);
                break;
            case 2:
                runWave(gameState);
                if (gameState->crystalHealth <= 0) {
                    gameLost = 1;
                }
                break;
            case 3:
                saveGame(gameState);
                break;
            case 4:
                if (loadGameInteractive(gameState)) {
                    printf("Game state restored!\n");
                }
                break;
            #ifdef DEBUG
                case 5:
                    findPath(gameState->gameBoard);
                    break;
                case 6:
                    runWave(gameState);
                    break;
            #endif
            default:
                printf("Invalid choice\n");
        }
        
        /* Check if player won */
        if (gameState->waveCount > MAX_WAVES) {
            printf("\n=== CONGRATULATIONS! ===\n");
            printf("You successfully defended the crystal through all %d waves!\n", MAX_WAVES);
            printf("Final Score - Crystal Health: %d, Money: %d\n", 
                   gameState->crystalHealth, gameState->playerMoney);
            gameLost = 1;
        }
    }
    
    if (gameState->crystalHealth <= 0) {
        printf("\n=== GAME OVER ===\n");
        printf("The crystal has been destroyed!\n");
        printf("You survived %d waves.\n", gameState->waveCount - 1);
    }
}

/*
 * Starts the next wave of enemies.
 * 
 * Input: gameState - pointer to current game state
 * Output: Increments waveCount
 */
void startNextWave(GameState_t *gameState) {
    gameState->waveCount++;
}
