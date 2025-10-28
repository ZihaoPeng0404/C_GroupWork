#include <stdio.h>  /* printf */
#include "board.h"

/*
 * Resets the game board to empty state.
 * 
 * Input: gameBoard - 2D array representing the game board
 * Output: Sets all tiles to EMPTY_TILE
 */
void resetBoard(char gameBoard[GRID_Y][GRID_X]) {
    int rowIndex;
    for (rowIndex = 0; rowIndex < GRID_Y; rowIndex++) {
        int columnIndex;
        for (columnIndex = 0; columnIndex < GRID_X; columnIndex++) {
            gameBoard[rowIndex][columnIndex] = EMPTY_TILE;
        }
    }
}

/*
 * Draws the current game board with borders and labels.
 * Displays crystal health, wave count, and player money.
 * 
 * Input: gameState - pointer to current game state
 * Output: Prints board to stdout
 */
void drawBoard(const GameState_t *gameState) {
    printf("\nCrystal Health: %d/%d   Wave: %d/%d   Money: %d$\n", 
           gameState->crystalHealth, MAX_CRYSTAL_HEALTH, 
           gameState->waveCount, MAX_WAVES, gameState->playerMoney);

    printf("#   #   ");
    int columnIndex;
    for (columnIndex = 1; columnIndex <= GRID_X; columnIndex++) {
        printf("%d   ", columnIndex);
    }
    printf("#   #\n");
    
    for (columnIndex = 1; columnIndex <= GRID_X + 4; columnIndex++) {
        printf("#   ");
    }
    printf("\n");

    int rowIndex;
    for (rowIndex = 0; rowIndex < GRID_Y; rowIndex++) {
        /* Handle portal placement */
        if (rowIndex == START_Y) {
            printf("%c   %c   ", 'A' + rowIndex, PORTAL_ENTRANCE);
        } else {
            printf("%c   %c   ", 'A' + rowIndex, TOWER_CHAR);
        }
        
        int columnIndex;
        for (columnIndex = 0; columnIndex < GRID_X; columnIndex++) {
            printf("%c   ", gameState->gameBoard[rowIndex][columnIndex]);
        }

        if (rowIndex == START_Y) {
            printf("%c   %c", PORTAL_EXIT, TOWER_CHAR);
        } else {
            printf("%c   %c", TOWER_CHAR, TOWER_CHAR);
        }
        printf("\n");
    }
    
    for (columnIndex = 1; columnIndex <= GRID_X + 4; columnIndex++) {
        printf("#   ");
    }
    printf("\n");
}
