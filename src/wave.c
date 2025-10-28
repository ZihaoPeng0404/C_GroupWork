#include <stdio.h>  /* printf */
#include "wave.h"
#include "pathfinding.h"
#include "board.h"
#include "game.h"

/*
 * Checks if a character represents an enemy.
 * 
 * Input: inputChar - character to check
 * Output: Returns 1 if enemy, 0 otherwise
 */
int isEnemy(char inputChar) {
    return (inputChar != EMPTY_TILE && inputChar != TOWER_CHAR);
}

/*
 * Damages enemy at given position when adjacent to tower.
 * Kills enemy if health reaches 0 and rewards player.
 * 
 * Input: columnPos - x coordinate
 *        rowPos - y coordinate
 *        gameState - pointer to current game state
 * Output: Modifies gameBoard and playerMoney
 */
void damageEnemy(int columnPos, int rowPos, GameState_t *gameState) {
    int directions[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    int directionIndex;
    
    for (directionIndex = 0; directionIndex < 4; directionIndex++) {
        if (gameState->gameBoard[rowPos][columnPos] == EMPTY_TILE) {
            continue;
        }

        int nextColumn = columnPos + directions[directionIndex][0];
        int nextRow = rowPos + directions[directionIndex][1];

        if (nextColumn < 0 || nextColumn >= GRID_X || 
            nextRow < 0 || nextRow >= GRID_Y) {
            continue;
        }
        
        if (gameState->gameBoard[nextRow][nextColumn] == TOWER_CHAR) {
            gameState->gameBoard[rowPos][columnPos] -= 1;
        }
        
        if (gameState->gameBoard[rowPos][columnPos] == '0') {
            gameState->playerMoney += ENEMY_REWARD;
            gameState->gameBoard[rowPos][columnPos] = EMPTY_TILE;
        }
    }
}

/*
 * Moves all enemies one step closer to the crystal along the path.
 * Damages crystal if enemy reaches it.
 * 
 * Input: gameState - pointer to current game state
 * Output: Modifies gameBoard and crystalHealth
 */
void moveEnemies(GameState_t *gameState) {
    Node_t current = getGoalNode();
    
    /* Check if enemy reached crystal */
    if (isEnemy(gameState->gameBoard[current.y][current.x])) {
        gameState->crystalHealth -= gameState->gameBoard[current.y][current.x] - ENEMY_CHAR_OFFSET;
        gameState->gameBoard[current.y][current.x] = EMPTY_TILE;
    }
    
    /* Move enemies along path from goal to start */
    while (current.x != START_X || current.y != START_Y) {
        Node_t parentNode = getParentNode(current.x, current.y);
        
        if (isEnemy(gameState->gameBoard[parentNode.y][parentNode.x])) {
            damageEnemy(parentNode.x, parentNode.y, gameState);
            gameState->gameBoard[current.y][current.x] = 
                gameState->gameBoard[parentNode.y][parentNode.x];
            gameState->gameBoard[parentNode.y][parentNode.x] = EMPTY_TILE;
        }
        current = parentNode;
    }
}

/*
 * Checks if any enemies are still on the board.
 * 
 * Input: gameState - pointer to current game state
 * Output: Returns 1 if enemies exist, 0 otherwise
 */
int anyEnemiesOnBoard(const GameState_t *gameState) {
    int columnIndex, rowIndex;
    
    for (rowIndex = 0; rowIndex < GRID_Y; rowIndex++) {
        for (columnIndex = 0; columnIndex < GRID_X; columnIndex++) {
            if (isEnemy(gameState->gameBoard[rowIndex][columnIndex])) {
                return 1;
            }
        }
    }
    return 0;
}

/*
 * Runs a wave of enemies spawning and moving toward the crystal.
 * Spawns number of enemies equal to waveCount at portal entrance.
 * 
 * Input: gameState - pointer to current game state
 * Output: Modifies gameBoard, crystalHealth, and increments waveCount
 */
void runWave(GameState_t *gameState) {
    findPath(gameState->gameBoard);

    int enemyIndex;
    for (enemyIndex = 0; enemyIndex < gameState->waveCount; enemyIndex++) {
        moveEnemies(gameState);
        gameState->gameBoard[START_Y][START_X] = ENEMY_CHAR_OFFSET + gameState->waveCount;
        drawBoard(gameState);

        /* Move enemies again without spawning one to add a gap */
        moveEnemies(gameState);
        drawBoard(gameState);
        
        int delayCounter;
        for (delayCounter = 0; delayCounter < GAME_DELAY; delayCounter++) {
            /* Delay loop */
        }
    }
    
    /* Continue moving enemies until all are gone */
    while (anyEnemiesOnBoard(gameState)) {
        moveEnemies(gameState);
        drawBoard(gameState);
        
        int delayCounter;
        for (delayCounter = 0; delayCounter < GAME_DELAY; delayCounter++) {
            /* Delay loop */
        }
    }
    
    gameState->waveCount++;
}
