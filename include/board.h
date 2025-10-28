#ifndef BOARD_H
#define BOARD_H

#include "game.h"

/* Function declarations */
void drawBoard(const GameState_t *gameState);
void resetBoard(char gameBoard[GRID_Y][GRID_X]);

#endif
