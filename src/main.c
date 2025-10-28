/*
 * Group: 1
 * Lab: 4
 * 
 * COMPILING INSTRUCTIONS:
 * - Standard build: make
 * - Debug build: make debug
 * - Clean build: make clean
 * - Run game: make run
 */

#include <stdio.h>  /* printf */
#include "game.h"
#include "save_load.h"

/*
 * Main entry point for Crystal Defense game.
 * Handles command line arguments for loading save files.
 * 
 * Input: argc - number of command line arguments
 *        argv - array of command line argument strings
 * Output: Returns 0 on successful completion
 */
int main(int argc, char *argv[]) {
    int loadedFromFile = 0;
    GameState_t gameState;
    
    /* Check if a save file was provided as command line argument */
    if (argc > 1) {
        printf("Loading save file: %s\n", argv[1]);
        
        /* Initialize game first */
        initGame(&gameState);
        
        /* Try to load the save file */
        if (loadGame(argv[1], &gameState)) {
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
        initGame(&gameState);
    }
    
    /* Start the main menu */
    mainMenu(&gameState);
    
    return 0;
}
