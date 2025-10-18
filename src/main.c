#include <stdio.h>
#include "game.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        /*load from file if provided*/ 
        printf("Loading save file: %s\n", argv[1]);
        /* implement loadGame() with filename later*/
    }

    initGame();
    mainMenu();
    return 0;
}
