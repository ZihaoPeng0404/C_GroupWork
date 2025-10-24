#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save_load.h"
#include "board.h"

#define ENCRYPTION_KEY 'K'
#define SAVE_DATA_SIZE 20

/* Structure to hold save data */
typedef struct {
    unsigned char compressedBoard[8];  /* 63 bits for 9x7 board */
    int crystalHealth;
    int waveCount;
    int playerMoney;
} SaveData;

/* XOR encryption/decryption function */
void xorEncryptDecrypt(char *data, int size, char key) {
    int i;
    for (i = 0; i < size; i++) {
        data[i] ^= key;
    }
}

/* Compress the game board into 8 bytes (64 bits, using 63 for 9x7 grid)
 * '.' = 0 (empty), '#' = 1 (tower) */
void compressBoard(unsigned char *compressed) {
    int x, y, bitIndex;
    
    /* Initialize compressed array to 0 */
    for (bitIndex = 0; bitIndex < 8; bitIndex++) {
        compressed[bitIndex] = 0;
    }
    
    bitIndex = 0;
    for (y = 0; y < GRID_Y; y++) {
        for (x = 0; x < GRID_X; x++) {
            if (gameBoard[y][x] == '#') {
                /* Set the bit at bitIndex */
                int byteIndex = bitIndex / 8;
                int bitPos = bitIndex % 8;
                compressed[byteIndex] |= (1 << bitPos);
            }
            bitIndex++;
        }
    }
}

/* Decompress the board from compressed format */
void decompressBoard(unsigned char *compressed) {
    int x, y, bitIndex;
    
    bitIndex = 0;
    for (y = 0; y < GRID_Y; y++) {
        for (x = 0; x < GRID_X; x++) {
            int byteIndex = bitIndex / 8;
            int bitPos = bitIndex % 8;
            
            /* Check if bit is set */
            if (compressed[byteIndex] & (1 << bitPos)) {
                gameBoard[y][x] = '#';
            } else {
                gameBoard[y][x] = '.';
            }
            bitIndex++;
        }
    }
}

/* Save the game to a file */
void saveGame(void) {
    char filename[256];
    FILE *file;
    SaveData saveData;
    
    printf("Enter filename to save (without extension): ");
    scanf("%255s", filename);
    
    /* Add .sav extension */
    strcat(filename, ".sav");
    
    /* Prepare save data */
    compressBoard(saveData.compressedBoard);
    saveData.crystalHealth = crystalHealth;
    saveData.waveCount = waveCount;
    saveData.playerMoney = playerMoney;
    
    /* Encrypt the data */
    xorEncryptDecrypt((char*)&saveData, SAVE_DATA_SIZE, ENCRYPTION_KEY);
    
    /* Write to file */
    file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Could not create save file!\n");
        return;
    }
    
    fwrite(&saveData, SAVE_DATA_SIZE, 1, file);
    fclose(file);
    
    printf("Game saved successfully to '%s'!\n", filename);
}

/* Load the game from a file */
int loadGame(const char *filename) {
    FILE *file;
    SaveData saveData;
    size_t bytesRead;
    
    /* Try to open the file */
    file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error: Could not open save file '%s'!\n", filename);
        return 0;
    }
    
    /* Read the data */
    bytesRead = fread(&saveData, 1, SAVE_DATA_SIZE, file);
    fclose(file);
    
    if (bytesRead != SAVE_DATA_SIZE) {
        printf("Error: Invalid save file format!\n");
        return 0;
    }
    
    /* Decrypt the data */
    xorEncryptDecrypt((char*)&saveData, SAVE_DATA_SIZE, ENCRYPTION_KEY);
    
    /* Validate the data (basic sanity checks) */
    if (saveData.crystalHealth < 0 || saveData.crystalHealth > 100 ||
        saveData.waveCount < 1 || saveData.waveCount > 10 ||
        saveData.playerMoney < 0 || saveData.playerMoney > 10000) {
        printf("Error: Save file is corrupted or encrypted with wrong key!\n");
        return 0;
    }
    
    /* Restore game state */
    decompressBoard(saveData.compressedBoard);
    crystalHealth = saveData.crystalHealth;
    waveCount = saveData.waveCount;
    playerMoney = saveData.playerMoney;
    
    printf("Game loaded successfully from '%s'!\n", filename);
    printf("Crystal Health: %d, Wave: %d, Money: %d\n", 
           crystalHealth, waveCount, playerMoney);
    
    return 1;
}

/* Interactive load - prompts user for filename */
int loadGameInteractive(void) {
    char filename[256];
    
    printf("Enter filename to load (without extension): ");
    scanf("%255s", filename);
    
    /* Add .sav extension */
    strcat(filename, ".sav");
    
    return loadGame(filename);
}
