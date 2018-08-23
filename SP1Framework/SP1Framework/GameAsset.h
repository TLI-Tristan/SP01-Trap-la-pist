#ifndef _GAME_ASSET
#define _GAME_ASSET

#include "Framework\console.h"
#include "game.h"

using namespace std;

void getDoublePiovtTrapPos (char map[100][100], struct SGameTrap &g_sDoublePiovtTrap);
void renderDoublePiovtTrap(Console &g_Console, struct SGameTrap g_sDoublePiovtTrap);
void doublePivotTrap(double &trapTime, struct SGameTrap &g_sDoublePiovtTrap, double &trapTime2);

void renderBouncingTrap(Console &g_Console, struct SGameTrap g_sBouncingTrap);
void bouncingTrap(double &g_dBouncingTrap, struct SGameTrap &g_sBouncingTrap);

void getMovingTrapPos(char map[100][100], struct SGameMovingTrap MovingTrap[8]);
void renderMovingTrap(Console &g_Console, struct SGameMovingTrap g_sMovingTrap[8]);
void movingTrap(double &trapTime, struct SGameMovingTrap g_sMovingTrap[8]);
void initMovingTrap(struct SGameMovingTrap g_sMovingTrap[8]);
void renderCharacter(Console &g_Console, struct SGameChar playerInfo);
void getFallingTrapPos(char map[100][100], struct SGameTrap g_fTrap[34]);
void fallingTrap(double &ftrapTime, struct SGameTrap g_fTrap[34]);
void renderFallingTrap(Console & g_Console, SGameTrap g_fTrap[34]);
void initFallingTrap(struct SGameTrap g_fTrap[34]);
void resetTrap(bool &bGotTrapPos, SGameTrap g_fTrap[34]);

void FanFunctionLeft(struct SGameChar &playerInfo, char mapStorage[100][100]);							 // Left fan function (movement & some checking)
void FanFunctionRight(struct SGameChar &playerInfo, char mapStorage[100][100], Console &g_console);		 // Right fan function (movement & some checking)
void FanFunctionUp(struct SGameChar &playerInfo, char mapStorage[100][100]);							 // Up fan function (movement & some checking)
void FanFunctionDown(struct SGameChar &playerInfo, char mapStorage[100][100], Console &g_console);		 // Down function (movement & some checking)
void FanFunctionMain(struct SGameChar &playerInfo, char mapStorage[100][100], Console &g_console);		 // Main fan function (checking)

void ArrayLevelOneDetect(struct SGameChar &playerInfo, int ChangesArrayOne[50]); // traps array detection (WIP)
void ArrayLevelOneActivate(struct SGameChar &playerInfo, int ChangesArrayOne[50], char mapStorage[100][100], struct SGameTrap g_fTrap[34], enum EGAMESTATES &g_eGameState); // traps array activate (WIP)

#endif