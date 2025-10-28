#include <stdio.h>  /* printf, scanf */
#include "tower.h"
#include "pathfinding.h"
#include "game.h"

/*
 * Checks if a character is a letter.
 * 
 * Input: inputChar - character to check
 * Output: Returns 1 if letter, 0 otherwise
 */
int isLetter(char inputChar) {
    return (inputChar >= 'a' && inputChar <= 'z') || 
           (inputChar >= 'A' && inputChar <= 'Z');
}

/*
 * Checks if a character is a digit.
 * 
 * Input: inputChar - character to check
 * Output: Returns 1 if digit, 0 otherwise
 */
int isDigit(char inputChar) {
    return (inputChar >= '0' && inputChar <= '9');
}

/*
 * Attempts to place a tower at user-specified coordinates.
 * Validates input, checks bounds, ensures valid path exists.
 * Deducts tower cost from player money if successful.
 * 
 * Input: gameState - pointer to current game state
 * Output: Modifies gameBoard and playerMoney in gameState
 */
void placeTower(GameState_t *gameState) {
    if (gameState->playerMoney < TOWER_COST) {
        printf("Not Enough Money\n");
        return;
    }
    
    char coord[4];
    int columnPos, rowPos;
    int validInput = 0;

    while (!validInput) {
        printf("Enter coordinates (e.g. a1, d5): ");
        if (scanf("%3s", coord) != 1) {
            printf("Invalid Input\n");
            /* Clear input buffer */
            int inputChar;
            while ((inputChar = getchar()) != '\n' && inputChar != EOF);
            continue;
        }

        /* Convert first letter to lowercase if needed */
        if (coord[0] >= 'A' && coord[0] <= 'Z') {
            coord[0] = coord[0] + 32;
        }

        /* Basic format check */
        if (!isLetter(coord[0]) || !isDigit(coord[1])) {
            printf("Invalid Input\n");
            continue;
        }

        /* Convert to zero-indexed coordinates */
        rowPos = coord[0] - 'a';
        int parsed = sscanf(coord + 1, "%d", &columnPos);
        if (parsed != 1) {
            printf("Invalid Input\n");
            continue;
        }
        columnPos--;

        /* Bounds check */
        if (columnPos < 0 || columnPos >= GRID_X || rowPos < 0 || rowPos >= GRID_Y) {
            printf("Out of bounds\n");
            continue;
        }

        /* Check for existing tower */
        if (gameState->gameBoard[rowPos][columnPos] == TOWER_CHAR) {
            printf("There is already a Tower there\n");
            continue;
        }

        /* Place tower temporarily */
        gameState->gameBoard[rowPos][columnPos] = TOWER_CHAR;

        /* Check for path to crystal */
        if (!findPath(gameState->gameBoard)) {
            gameState->gameBoard[rowPos][columnPos] = EMPTY_TILE;
            printf("There has to be a valid path to the crystal\n");
            continue;
        }

           printf("Tower placed at %c%d\n", 'a' + rowPos, columnPos + 1);
        validInput = 1;
    }
    
    gameState->playerMoney -= TOWER_COST;
}
