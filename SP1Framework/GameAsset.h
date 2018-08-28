#ifndef _GAME_ASSET
#define _GAME_ASSET

#include "Framework\console.h"
#include "game.h"
#include <random>

using namespace std;

struct storage {
	COORD m_cLocation;
};



void getRandomMovementTrapPos(char map[100][100], struct SGameTrap g_sRandomMovementTrap[28]);
void randomMovementTrap(double &trapTime, struct SGameTrap g_sRandomMovementTrap[28]);
void renderRandomMvementTrap(Console &g_Console, struct SGameTrap g_sRandomMovementTrap[28]);

void getDoublePiovtTrapPos (char map[100][100], struct SGameTrap &g_sDoublePiovtTrap);
void renderDoublePiovtTrap(Console &g_Console, struct SGameTrap g_sDoublePiovtTrap);
void doublePivotTrap(double &trapTime, struct SGameTrap &g_sDoublePiovtTrap, double &trapTime2);

void renderBouncingTrap(Console &g_Console, struct SGameTrap g_sBouncingTrap, struct storage lineArray[100]);
void bouncingTrap(double &g_dBouncingTrap, struct SGameTrap &g_sBouncingTrap, struct storage lineArray[100]);

void getChargeTrapPos(char map[100][100], struct SGameTrap ChargeTrap[12]);
void renderChargeTrap(Console &g_Console, struct SGameTrap g_sChargeTrap[12]);
void chargeTrap(double &trapTime, struct SGameTrap g_sChargeTrap[12]);


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
void resetTrap2(bool &bGotTrapPos2);
void resetLineArray(struct storage lineArray[100]);

void ArrayLevelOneDetect(struct SGameChar &playerInfo, int ChangesArrayOne[50]); // traps array detection
void ArrayLevelOneActivate(struct SGameChar &playerInfo, int ChangesArrayOne[50], char mapStorage[100][100], struct SGameTrap g_fTrap[34], enum EGAMESTATES &g_eGameState); // traps array activate
void ArrayLevelTwoDetect(struct SGameChar &playerInfo, int ChangesArrayTwo[50]); // traps array detection
void ArrayLevelTwoActivate(struct SGameChar &playerInfo, int ChangesArrayTwo[50], char mapStorage[100][100], enum EGAMESTATES &g_eGameState); // traps array activate



void StalkerFunctionMain(struct SGameChar &playerInfo, char mapStorage[100][100], SGameTrap g_sStalkerTrap[7]);
void StalkerFunctionMovement(double &sTrapTime, struct SGameChar &playerInfo, char mapStorage[100][100], SGameTrap g_sStalkerTrap[7]);
void getStalkerTrapPos(char map[100][100], struct SGameTrap g_sStalkerTrap[7]);
void renderStalkerTrap(Console &g_Console, struct SGameTrap g_sStalkerTrap[7]);

void getFanTrapPos(char map[100][100], struct SGameTrap g_leftFanTrap[5], struct SGameTrap g_rightFanTrap[5], struct SGameTrap g_upFanTrap[5], struct SGameTrap g_downFanTrap[5]);
void FanFunctionMain(struct SGameChar &playerInfo, char mapStorage[100][100], Console &g_console, struct SGameTrap g_leftFanTrap[5], struct SGameTrap g_rightFanTrap[5], struct SGameTrap g_upFanTrap[5], struct SGameTrap g_downFanTrap[5]);
void leftFanMovement(double &leftFanTrapTime, struct SGameChar &playerInfo, char mapStorage[100][100], SGameTrap g_leftFanTrap[5]);
void rightFanMovement(double &rightFanTrapTime, struct SGameChar &playerInfo, char mapStorage[100][100], SGameTrap g_rightFanTrap[5]);
void upFanMovement(double &upFanTrapTime, struct SGameChar &playerInfo, char mapStorage[100][100], SGameTrap g_upFanTrap[5]);
void downFanMovement(double &downFanTrapTime, struct SGameChar &playerInfo, char mapStorage[100][100], SGameTrap g_downFanTrap[5]);

#endif