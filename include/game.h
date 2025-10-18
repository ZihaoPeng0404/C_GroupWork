#ifndef GAME_H
#define GAME_H

#define GRID_X 9
#define GRID_Y 7

extern char gameBoard[GRID_Y][GRID_X];
extern int crystalHealth;
extern int waveCount;
extern int playerMoney;

void initGame(void);
void mainMenu(void);
void startNextWave(void);

#endif
