#include "GameAsset.h"

SGameTrap g_fTrap01;
int FanBlowLeftDelay = 0, FanBlowRightDelay = 0, FanBlowUpDelay = 0, FanBlowDownDelay = 0;
int AllowedMaxFanDelay = 3; // maximum frames allowed for delay CAN BE EDITED

void getMovingTrapPos(bool &bGotTrapPos, char map[100][100], struct SGameTrap g_sMovingTrap[8]) {

	int i = 0;
	for (int k = 0; k < 30; k++) {

		for (int j = 0; j < 80; j++) {
			if (map[k][j] == 'A') {
				g_sMovingTrap[i].m_cLocation.X = j;
				g_sMovingTrap[i].m_cLocation.Y = k + 1;
				i++;

			}
		}
	}
	bGotTrapPos = true;
}


void initMovingTrap(struct SGameTrap g_sMovingTrap[8]) {

	for (int i = 0; i < 8; i++) {

		g_sMovingTrap[i].m_cDirection = 1;
	}
}


void movingTrap(double &trapTime, struct SGameTrap g_sMovingTrap[8]) {

	if (trapTime >= 0.1) {

		for (int i = 0; i < 8; i++) {



			if (g_sMovingTrap[i].m_cLocation.Y == 13) {
				g_sMovingTrap[i].m_cDirection = 1;
			}

			if (i <= 4 && i >= 2) {
				if (g_sMovingTrap[i].m_cLocation.Y == 17) {
					g_sMovingTrap[i].m_cDirection = -1;
				}
			}
			else if (g_sMovingTrap[i].m_cLocation.Y == 18) {
				g_sMovingTrap[i].m_cDirection = -1;
			}
			g_sMovingTrap[i].m_cLocation.Y += g_sMovingTrap[i].m_cDirection;


		}
		trapTime = 0.0;
	}
}

void renderMovingTrap(Console &g_Console, struct SGameTrap g_sMovingTrap[8]) {

	WORD trapColor = 0x0C;
	{
		trapColor = 0x0A;
	}
	for (int i = 0; i < 8; i++) {
		g_Console.writeToBuffer(g_sMovingTrap[i].m_cLocation, "A", trapColor);
	}
}

void renderFallingTrap(Console &g_console)
{
	WORD trapColor = 0x0C;
	{
		trapColor = 0x0A;
	}
	g_console.writeToBuffer(g_fTrap01.m_cLocation, (char)4, trapColor);
}

void renderCharacter(Console &g_Console, struct SGameChar playerInfo)
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	if (playerInfo.m_bActive)
	{
		charColor = 0x0A;
	}
	g_Console.writeToBuffer(playerInfo.m_cLocation, (char)1, charColor);
}

// START FAN FUNCTION //
void FanFunctionMain(struct SGameChar &playerInfo, char mapStorage[100][100], Console &g_console)
{
	if (/*mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 29] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 28] == 'N' ||
		mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 27] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 26] == 'N' ||
		mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 25] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 24] == 'N' ||
		mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 23] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 22] == 'N' ||
		mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 21] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 20] == 'N' ||
		mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 19] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 18] == 'N' ||
		mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 17] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 16] == 'N' ||
		mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 15] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 14] == 'N' ||
		mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 13] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 12] == 'N' ||					// include if want larger fan blowing distance
		mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 11] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 10] == 'N' ||*/
		mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X + 9] == 'N' || mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X + 8] == 'N' ||
		mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X + 7] == 'N' || mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X + 6] == 'N' ||
		mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X + 5] == 'N' || mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X + 4] == 'N' ||
		mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X + 3] == 'N' || mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X + 2] == 'N' ||
		mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X + 1] == 'N' || mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X] == 'N')
	{
		FanFunctionLeft(playerInfo, mapStorage); // call fanfunctionleft
	}

	if (mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X - 9] == 'M' || mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X - 8] == 'M' ||
		mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X - 7] == 'M' || mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X - 6] == 'M' ||
		mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X - 5] == 'M' || mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X - 4] == 'M' ||
		mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X - 3] == 'M' || mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X - 2] == 'M' ||
		mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X - 1] == 'M' || mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X] == 'M')
	{
		FanFunctionRight(playerInfo, mapStorage, g_console); // call fanfunctionright
	}

	if (mapStorage[(int)playerInfo.m_cLocation.Y + 9][(int)playerInfo.m_cLocation.X] == 'Z' || mapStorage[(int)playerInfo.m_cLocation.Y + 8][(int)playerInfo.m_cLocation.X] == 'Z' ||
		mapStorage[(int)playerInfo.m_cLocation.Y + 7][(int)playerInfo.m_cLocation.X] == 'Z' || mapStorage[(int)playerInfo.m_cLocation.Y + 6][(int)playerInfo.m_cLocation.X] == 'Z' ||
		mapStorage[(int)playerInfo.m_cLocation.Y + 5][(int)playerInfo.m_cLocation.X] == 'Z' || mapStorage[(int)playerInfo.m_cLocation.Y + 4][(int)playerInfo.m_cLocation.X] == 'Z' ||
		mapStorage[(int)playerInfo.m_cLocation.Y + 3][(int)playerInfo.m_cLocation.X] == 'Z' || mapStorage[(int)playerInfo.m_cLocation.Y + 2][(int)playerInfo.m_cLocation.X] == 'Z' ||
		mapStorage[(int)playerInfo.m_cLocation.Y + 1][(int)playerInfo.m_cLocation.X] == 'Z' || mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X] == 'Z' ||
		mapStorage[(int)playerInfo.m_cLocation.Y][(int)playerInfo.m_cLocation.X] == 'Z')
	{
		FanFunctionUp(playerInfo, mapStorage); // call fanfunctionup
	}

	if (mapStorage[(int)playerInfo.m_cLocation.Y - 9][(int)playerInfo.m_cLocation.X] == 'X' || mapStorage[(int)playerInfo.m_cLocation.Y - 8][(int)playerInfo.m_cLocation.X] == 'X' ||
		mapStorage[(int)playerInfo.m_cLocation.Y - 7][(int)playerInfo.m_cLocation.X] == 'X' || mapStorage[(int)playerInfo.m_cLocation.Y - 6][(int)playerInfo.m_cLocation.X] == 'X' ||
		mapStorage[(int)playerInfo.m_cLocation.Y - 5][(int)playerInfo.m_cLocation.X] == 'X' || mapStorage[(int)playerInfo.m_cLocation.Y - 4][(int)playerInfo.m_cLocation.X] == 'X' ||
		mapStorage[(int)playerInfo.m_cLocation.Y - 3][(int)playerInfo.m_cLocation.X] == 'X' || mapStorage[(int)playerInfo.m_cLocation.Y - 2][(int)playerInfo.m_cLocation.X] == 'X' ||
		mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X] == 'X' || mapStorage[(int)playerInfo.m_cLocation.Y][(int)playerInfo.m_cLocation.X] == 'X')
	{
		FanFunctionDown(playerInfo, mapStorage, g_console); // call fanfunctiondown
	}
}


void FanFunctionLeft(struct SGameChar &playerInfo, char mapStorage[100][100])
{
	if (FanBlowLeftDelay < AllowedMaxFanDelay) // left fan
	{
		FanBlowLeftDelay++;
	}
	else if (FanBlowLeftDelay == AllowedMaxFanDelay && mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X - 1] != '#' && mapStorage[(int)playerInfo.m_cLocation.Y - 2][(int)playerInfo.m_cLocation.X] != 'D')
	{
		if (playerInfo.m_cLocation.X > 0 && playerInfo.m_cLocation.X < 79)
		{
			playerInfo.m_cLocation.X--;
		}
		FanBlowLeftDelay = 0;
	}

}

void FanFunctionRight(struct SGameChar &playerInfo, char mapStorage[100][100], Console &g_console)
{
	if (FanBlowRightDelay < AllowedMaxFanDelay) // right fan
	{
		FanBlowRightDelay++;
	}
	else if (FanBlowRightDelay == AllowedMaxFanDelay)
	{
		if (playerInfo.m_cLocation.X < g_console.getConsoleSize().X - 41 && mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X + 1] != '#' && mapStorage[(int)playerInfo.m_cLocation.Y - 2][(int)playerInfo.m_cLocation.X] != 'D')
		{
			playerInfo.m_cLocation.X++;
		}
		FanBlowRightDelay = 0;
	}
}

void FanFunctionUp(struct SGameChar &playerInfo, char mapStorage[100][100])
{
	if (FanBlowUpDelay < AllowedMaxFanDelay) // up fan // unable to push player if player is IN UP fan
	{
		FanBlowUpDelay++;
	}
	else if (FanBlowUpDelay == AllowedMaxFanDelay)
	{
		if (playerInfo.m_cLocation.Y > 2 && mapStorage[(int)playerInfo.m_cLocation.Y - 2][(int)playerInfo.m_cLocation.X] != '#' && mapStorage[(int)playerInfo.m_cLocation.Y - 2][(int)playerInfo.m_cLocation.X] != 'D')
		{
			playerInfo.m_cLocation.Y--;
		}
		FanBlowUpDelay = 0;
	}
}

void FanFunctionDown(struct SGameChar &playerInfo, char mapStorage[100][100], Console &g_console)
{
	if (FanBlowDownDelay < AllowedMaxFanDelay) // down fan
	{
		FanBlowDownDelay++;
	}
	else if (FanBlowDownDelay == AllowedMaxFanDelay)
	{
		if (playerInfo.m_cLocation.Y < g_console.getConsoleSize().Y - 7 && mapStorage[(int)playerInfo.m_cLocation.Y][(int)playerInfo.m_cLocation.X] != '#' && mapStorage[(int)playerInfo.m_cLocation.Y - 2][(int)playerInfo.m_cLocation.X] != 'D')
		{
			playerInfo.m_cLocation.Y++;
		}
		FanBlowDownDelay = 0;
	}
}
// END FAN FUNCTION //



//================
//====  WIP  =====
//================

// hell again "framework for changes array" <<WIP>>
void ArrayLevelOneDetect(struct SGameChar &playerInfo, int ChangesArrayOne[50])
{
	if (((int)playerInfo.m_cLocation.Y - 1 == 27 && (int)playerInfo.m_cLocation.X == 28) || ((int)playerInfo.m_cLocation.Y - 1 == 25 && (int)playerInfo.m_cLocation.X == 28))
	{
		ChangesArrayOne[1] = 1; // for second 2 pressure plates
	}
	// etc etc
}

// "framework for changes array RESET" <<WIP>>
void ArrayLevelOneActivate(struct SGameChar &playerInfo, int ChangesArrayOne[50], char mapStorage[100][100])
{
	if (ChangesArrayOne[1] == 1)
	{
		mapStorage[26][68] = ','; // opens 1st door
	}
	// etc etc
}