#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "game.h"

void saveGame(void);
int loadGame(const char *filename);
int loadGameInteractive(void);
void xorEncryptDecrypt(char *data, int size, char key);

#endif
