#ifndef GAME_H
#define GAME_H

#include <stdio.h>  /* FILE */

#define GRID_X 9
#define GRID_Y 7
#define GAME_DELAY 100000000

/* Game constants */
#define MAX_CRYSTAL_HEALTH 100
#define INITIAL_CRYSTAL_HEALTH 100
#define INITIAL_WAVE_COUNT 1
#define MAX_WAVES 10
#define INITIAL_PLAYER_MONEY 200
#define TOWER_COST 100
#define ENEMY_REWARD 50
#define MAX_PLAYER_MONEY 10000

/* Game board characters */
#define EMPTY_TILE '.'
#define TOWER_CHAR '#'
#define ENEMY_CHAR_OFFSET '0'
#define PORTAL_ENTRANCE '@'
#define PORTAL_EXIT 'O'

/* Pathfinding constants */
#define START_X 8
#define START_Y 3
#define GOAL_X 0
#define GOAL_Y 3

/* Priority Queue */
#define MAX_QUEUE_SIZE 100

/* Game state structure */
typedef struct {
    char gameBoard[GRID_Y][GRID_X];
    int crystalHealth;
    int waveCount;
    int playerMoney;
} GameState_t;

/* Function declarations */
void initGame(GameState_t *gameState);
void mainMenu(GameState_t *gameState);
void startNextWave(GameState_t *gameState);

#endif
