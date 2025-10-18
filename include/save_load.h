#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "game.h"

void saveGame(void);
int loadGame(void);
void xorEncryptDecrypt(char *data, int size, char key);

#endif
