#include <stdio.h>  /* printf, scanf, fread, fwrite, fopen, fclose */
#include <stdlib.h>
#include <string.h>  /* strcat */
#include "save_load.h"
#include "board.h"

/* Save file related constants */
#define MAX_FILENAME_LENGTH 256
#define FILENAME_EXTENSION ".sav"

/*
 * Encrypts or decrypts data using XOR with given key.
 * 
 * Input: data - pointer to data to encrypt/decrypt
 *        size - size of data in bytes
 *        key - encryption key
 * Output: Modifies data in place
 */
void xorEncryptDecrypt(char *data, int size, char key) {
    int index;
    for (index = 0; index < size; index++) {
        data[index] ^= key;
    }
}

/*
 * Compresses the game board into 8 bytes using bit packing.
 * '.' = 0 (empty), '#' = 1 (tower)
 * 
 * Input: gameBoard - 2D array representing board state
 *        compressed - output array for compressed data
 * Output: Modifies compressed array
 */
void compressBoard(const char gameBoard[GRID_Y][GRID_X], 
                   unsigned char *compressed) {
    int columnIndex, rowIndex, bitIndex;
    
    /* Initialize compressed array to 0 */
    for (bitIndex = 0; bitIndex < 8; bitIndex++) {
        compressed[bitIndex] = 0;
    }
    
    bitIndex = 0;
    for (rowIndex = 0; rowIndex < GRID_Y; rowIndex++) {
        for (columnIndex = 0; columnIndex < GRID_X; columnIndex++) {
            if (gameBoard[rowIndex][columnIndex] == TOWER_CHAR) {
                /* Set the bit at bitIndex */
                int byteIndex = bitIndex / 8;
                int bitPos = bitIndex % 8;
                compressed[byteIndex] |= (1 << bitPos);
            }
            bitIndex++;
        }
    }
}

/*
 * Decompresses the board from compressed format.
 * 
 * Input: compressed - compressed board data
 *        gameBoard - output array for decompressed board
 * Output: Modifies gameBoard array
 */
void decompressBoard(const unsigned char *compressed, 
                     char gameBoard[GRID_Y][GRID_X]) {
    int columnIndex, rowIndex, bitIndex;
    
    bitIndex = 0;
    for (rowIndex = 0; rowIndex < GRID_Y; rowIndex++) {
        for (columnIndex = 0; columnIndex < GRID_X; columnIndex++) {
            int byteIndex = bitIndex / 8;
            int bitPos = bitIndex % 8;
            
            /* Check if bit is set */
            if (compressed[byteIndex] & (1 << bitPos)) {
                gameBoard[rowIndex][columnIndex] = TOWER_CHAR;
            } else {
                gameBoard[rowIndex][columnIndex] = EMPTY_TILE;
            }
            bitIndex++;
        }
    }
}

/*
 * Saves the current game state to a file with encryption.
 * 
 * Input: gameState - pointer to current game state
 * Output: Creates save file on disk
 */
void saveGame(const GameState_t *gameState) {
    char filename[MAX_FILENAME_LENGTH];
    FILE *file;
    SaveData_t saveData;
    
    printf("Enter filename to save (without extension): ");
    if (scanf("%255s", filename) != 1) {
        printf("Error: Invalid filename input!\n");
        return;
    }
    
    /* Add .sav extension */
    strcat(filename, FILENAME_EXTENSION);
    
    /* Prepare save data */
    compressBoard(gameState->gameBoard, saveData.compressedBoard);
    saveData.crystalHealth = gameState->crystalHealth;
    saveData.waveCount = gameState->waveCount;
    saveData.playerMoney = gameState->playerMoney;
    
    /* Encrypt the data */
    xorEncryptDecrypt((char*)&saveData, sizeof(SaveData_t), ENCRYPTION_KEY);
    
    /* Write to file */
    file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Could not create save file!\n");
        return;
    }
    
    fwrite(&saveData, sizeof(SaveData_t), 1, file);
    fclose(file);
    
    printf("Game saved successfully to '%s'!\n", filename);
}

/*
 * Loads game state from a file and decrypts it.
 * 
 * Input: filename - path to save file
 *        gameState - pointer to game state to populate
 * Output: Returns 1 if successful, 0 otherwise
 */
int loadGame(const char *filename, GameState_t *gameState) {
    FILE *file;
    SaveData_t saveData;
    size_t bytesRead;
    
    /* Try to open the file */
    file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error: Could not open save file '%s'!\n", filename);
        return 0;
    }
    
    /* Read the data */
    bytesRead = fread(&saveData, 1, sizeof(SaveData_t), file);
    fclose(file);
    
    if (bytesRead != sizeof(SaveData_t)) {
        printf("Error: Invalid save file format!\n");
        return 0;
    }
    
    /* Decrypt the data */
    xorEncryptDecrypt((char*)&saveData, sizeof(SaveData_t), ENCRYPTION_KEY);
    
    /* Validate the data (basic sanity checks) */
    if (saveData.crystalHealth < 0 || saveData.crystalHealth > MAX_CRYSTAL_HEALTH ||
        saveData.waveCount < 1 || saveData.waveCount > MAX_WAVES ||
        saveData.playerMoney < 0 || saveData.playerMoney > MAX_PLAYER_MONEY) {
        printf("Error: Save file is corrupted or encrypted with wrong key!\n");
        return 0;
    }
    
    /* Restore game state */
    decompressBoard(saveData.compressedBoard, gameState->gameBoard);
    gameState->crystalHealth = saveData.crystalHealth;
    gameState->waveCount = saveData.waveCount;
    gameState->playerMoney = saveData.playerMoney;
    
    printf("Game loaded successfully from '%s'!\n", filename);
    printf("Crystal Health: %d, Wave: %d, Money: %d\n", 
           gameState->crystalHealth, gameState->waveCount, gameState->playerMoney);
    
    return 1;
}

/*
 * Interactive load - prompts user for filename.
 * 
 * Input: gameState - pointer to game state to populate
 * Output: Returns 1 if successful, 0 otherwise
 */
int loadGameInteractive(GameState_t *gameState) {
    char filename[MAX_FILENAME_LENGTH];
    
    printf("Enter filename to load (without extension): ");
    if (scanf("%255s", filename) != 1) {
        printf("Error: Invalid filename input!\n");
        return 0;
    }
    
    /* Add .sav extension */
    strcat(filename, FILENAME_EXTENSION);
    
    return loadGame(filename, gameState);
}
