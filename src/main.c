#include <stdio.h>
#include "game.h"
#include "save_load.h"

int main(int argc, char *argv[]) {
    int loadedFromFile = 0;
    
    /* Check if a save file was provided as command line argument */
    if (argc > 1) {
        printf("Loading save file: %s\n", argv[1]);
        
        /* Initialize game first */
        initGame();
        
        /* Try to load the save file */
        if (loadGame(argv[1])) {
            loadedFromFile = 1;
            printf("Starting game from saved state...\n\n");
        } else {
            printf("Failed to load save file. Starting new game...\n\n");
        }
    }
    
    /* If no save file was loaded, initialize a new game */
    if (!loadedFromFile) {
        printf("=== CRYSTAL DEFENSE ===\n");
        printf("Defend your crystal from waves of enemies!\n\n");
        initGame();
    }
    
    /* Start the main menu */
    mainMenu();
    
    return 0;
}
