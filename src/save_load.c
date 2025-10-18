#include <stdio.h>
#include <stdlib.h>
#include "save_load.h"

void xorEncryptDecrypt(char *data, int size, char key) {
    int i;
    for (i = 0; i < size; i++) {
        data[i] ^= key;
    }
}

void saveGame(void) {
}

int loadGame(void) {
    return 0;
}
