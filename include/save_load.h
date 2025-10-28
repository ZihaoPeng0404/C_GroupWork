#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "game.h"

/* Save file encryption key */
#define ENCRYPTION_KEY 'K'

/* Save data structure */
typedef struct {
    unsigned char compressedBoard[8];  /* 63 bits for 9x7 board */
    int crystalHealth;
    int waveCount;
    int playerMoney;
} SaveData_t;

/* Function declarations */
void saveGame(const GameState_t *gameState);
int loadGame(const char *filename, GameState_t *gameState);
int loadGameInteractive(GameState_t *gameState);
void xorEncryptDecrypt(char *data, int size, char key);
void compressBoard(const char gameBoard[GRID_Y][GRID_X], unsigned char *compressed);
void decompressBoard(const unsigned char *compressed, char gameBoard[GRID_Y][GRID_X]);

#endif
