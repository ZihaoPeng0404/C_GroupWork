#ifndef WAVE_H
#define WAVE_H

#include "game.h"

/* Function declarations */
void runWave(GameState_t *gameState);
int isEnemy(char inputChar);
void damageEnemy(int columnPos, int rowPos, GameState_t *gameState);
void moveEnemies(GameState_t *gameState);
int anyEnemiesOnBoard(const GameState_t *gameState);

#endif
