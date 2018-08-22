#include "GameAsset.h"

int FanBlowLeftDelay = 0, FanBlowRightDelay = 0, FanBlowUpDelay = 0, FanBlowDownDelay = 0;
int AllowedMaxFanDelay = 3; // maximum frames allowed for delay CAN BE EDITED

bool bTriggerFallTrap = false;

void getMovingTrapPos(char map[100][100], struct SGameMovingTrap g_sMovingTrap[8]) {

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
}

void getFallingTrapPos(char map[100][100], struct SGameTrap g_fTrap[34]) {

	int i = 0;
	for (int k = 0; k < 30; k++) {

		for (int j = 0; j < 80; j++) {
			if (map[k][j] == 'T') {
				g_fTrap[i].m_cLocation.X = j;
				g_fTrap[i].m_cLocation.Y = k + 1;
				i++;

			}
		}
	}
}

void getDoublePiovtTrapPos(char map[100][100], struct SGameTrap &g_sDoublePiovtTrap) {

	for (int k = 0; k < 30; k++) {

		for (int j = 0; j < 80; j++) {

			if (map[k][j] == 'Q') {
				g_sDoublePiovtTrap.m_cLocation.X = j;
				g_sDoublePiovtTrap.m_cLocation.Y = k + 9;

			}
		}
	}

}

void initMovingTrap(struct SGameMovingTrap g_sMovingTrap[8]) {

	for (int i = 0; i < 8; i++) {

		g_sMovingTrap[i].m_cDirection = 1;
	}
}

void initFallingTrap(struct SGameTrap g_fTrap[34]) {

	for (int i = 0; i < 34; i++) {

		g_fTrap[i].m_bActive = true;

	}
}

void movingTrap(double &trapTime, struct SGameMovingTrap g_sMovingTrap[8]) {


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

void FallingTrap(double &ftrapTime, struct SGameTrap g_fTrap[34])
{
		if (ftrapTime >= 0.5 && bTriggerFallTrap == true)
		{

			for (int i = 0; i < 34; i++)
			{


				if (g_fTrap[i].m_cLocation.Y == 11) {
					g_fTrap[i].m_bActive = false;
				}
				else {
					g_fTrap[i].m_cLocation.Y += 1;
				}


				if (g_fTrap[i].m_bActive == false) {
					g_fTrap[i].m_cLocation.X = 1;
					g_fTrap[i].m_cLocation.Y = 1;
				}

			}
			ftrapTime = 0.0;
		
	}


}

int x = 20;
int y = -8;
int rotation = 1;
int rotation2 = 1;
int x2 = -7;
int y2 = 3;
void DoublePivotTrap(double &trapTime, struct SGameTrap &g_sDoublePiovtTrap, double &trapTime2) {

	if (trapTime2 >= 0.1) {

		g_sDoublePiovtTrap.m_cLocation.X += x2;
		g_sDoublePiovtTrap.m_cLocation.Y += y2;

		if (rotation2 == 1) {
			rotation2 += 1;
			x2 = 7;
			y2 = 0;
		}
		else if (rotation2 == 2) {
			rotation2 += 1;
		}
		else if (rotation2 == 3) {
			rotation2 += 1;
			y2 = -3;
			x2 = 0;
		}
		else if (rotation2 == 4) {
			rotation2 += 1;
		}
		else if (rotation2 == 5) {
			rotation2 += 1;
			x2 = -7;
			y2 = 0;
		}
		else if (rotation2 == 6) {
			rotation2 += 1;
		}
		else if (rotation2 == 7) {
			rotation2 += 1;
			y2 = 3;
			x2 = 0;
		}
		else if (rotation2 == 8) {

			rotation2 = 1;
		}

		trapTime2 = 0.0;
	}





	if (trapTime >= 0.6) {
	
		g_sDoublePiovtTrap.m_cLocation.X += x;
		g_sDoublePiovtTrap.m_cLocation.Y += y;

		


		if (rotation == 1) {
			rotation += 1;
			x *= -1;
		}
		else if (rotation == 2) {
			rotation += 1;
			y *= -1;
		}
		else if (rotation == 3) {
			rotation += 1;
			x *= -1;
		}
		else if (rotation == 4) {

			y *= -1;
			rotation = 1;
		}

		trapTime = 0.0;
	}

}

void resetTrap(bool &bGotTrapPos, SGameTrap g_fTrap[34]) {

	bTriggerFallTrap = false;
	bGotTrapPos = false;
	for (int i = 0; i < 34; i++) {
		g_fTrap[i].m_bActive = true;
	}
}

void renderMovingTrap(Console &g_Console, struct SGameMovingTrap g_sMovingTrap[8]) {

	WORD trapColor = 0x0C;
	{
		trapColor = 0x0A;
	}
	for (int i = 0; i < 8; i++) {
		g_Console.writeToBuffer(g_sMovingTrap[i].m_cLocation, "A", trapColor);
	}
}

void renderFallingTrap(Console &g_Console, SGameTrap g_fTrap[34])
{
	WORD trapColor = 0x0C;
	{
		trapColor = 0x30;
	}
	
	for (int i = 0; i < 34; i++) {
		if (g_fTrap[i].m_bActive == true) {
			g_Console.writeToBuffer(g_fTrap[i].m_cLocation, "T", trapColor);
		}
	}
}

void renderDoublePiovtTrap(Console &g_Console, struct SGameTrap g_sDoublePiovtTrap) {

	WORD trapColor = 0x0C;
	{
		trapColor = 0x0A;
	}
		g_Console.writeToBuffer(g_sDoublePiovtTrap.m_cLocation, "Q", trapColor);
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



// LEGEND:
// ',' (Comma) = Deactivated Door
// '.' (FullStop) = Deactivated Electric Floor
// 'b' (b) = Deactivated Spikes
// 'l' (l) = Deactivated Fans

// Detect pressure plates etc presses (Level One)
void ArrayLevelOneDetect(struct SGameChar &playerInfo, int ChangesArrayOne[50])
{
	if (((int)playerInfo.m_cLocation.Y - 1 == 27 && (int)playerInfo.m_cLocation.X == 28) || ((int)playerInfo.m_cLocation.Y - 1 == 25 && (int)playerInfo.m_cLocation.X == 28))
	{
		ChangesArrayOne[1] = 1; // for second 2 pressure plates
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 23 && (int)playerInfo.m_cLocation.X == 70) // for pressure plate after "2 fake pressure plate"
	{
		ChangesArrayOne[2] = 1;
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 19 && (int)playerInfo.m_cLocation.X == 64) // for top left at room with 2nd checkpoint
	{
		ChangesArrayOne[3] = 1;
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 23 && (int)playerInfo.m_cLocation.X == 59) // for bottome left at room with 2nd checkpoint
	{
		ChangesArrayOne[4] = 1;
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 18 && (int)playerInfo.m_cLocation.X == 78) // for top right at room with 2nd checkpoint
	{
		ChangesArrayOne[5] = 1;
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 13 && (int)playerInfo.m_cLocation.X == 78) // for rightmost generator
	{
		ChangesArrayOne[6] = 1;
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 16 && (int)playerInfo.m_cLocation.X == 71) // for pressure plate between spikes
	{
		ChangesArrayOne[7] = 1;
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 14 && (int)playerInfo.m_cLocation.X == 1) // for leftmost pressure plate
	{
		ChangesArrayOne[8] = 1;
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 15 && (int)playerInfo.m_cLocation.X == 1) // for leftmost generator
	{
		ChangesArrayOne[9] = 1;
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 10 && (int)playerInfo.m_cLocation.X == 16 || (int)playerInfo.m_cLocation.Y - 1 == 10 && (int)playerInfo.m_cLocation.X == 17) // for falling trap row room pressure plate
	{
		ChangesArrayOne[10] = 1;
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 10 && (int)playerInfo.m_cLocation.X == 49) // for spike room generator
	{
		ChangesArrayOne[11] = 1;
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 10 && (int)playerInfo.m_cLocation.X == 52) // for spike room leftmost pressure plate
	{
		ChangesArrayOne[12] = 1;
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 27 && (int)playerInfo.m_cLocation.X == 26) // Fans
	{
		ChangesArrayOne[13] = 1;
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 1 && (int)playerInfo.m_cLocation.X == 79) // Victory
	{
		ChangesArrayOne[14] = 1;
	}
}

// Activate traps function (Level One)
void ArrayLevelOneActivate(struct SGameChar &playerInfo, int ChangesArrayOne[50], char mapStorage[100][100], struct SGameTrap g_fTrap[34], enum EGAMESTATES &g_eGameState)
{
	if (ChangesArrayOne[1] == 1)
	{
		mapStorage[26][68] = ','; // opens 1st door
	}
	if (ChangesArrayOne[2] == 1)
	{
		mapStorage[22][78] = 'b'; // removes bottom right spike at 2nd checkpoint room
	}
	if (ChangesArrayOne[3] == 1)
	{
		mapStorage[23][64] = 'b';// removes bottom left spike at 2nd checkpoint room
	}
	if (ChangesArrayOne[4] == 1)
	{
		mapStorage[20][71] = 'b'; // removes top right spike at 2nd checkpoint room
	}
	if (ChangesArrayOne[5] == 1)
	{
		mapStorage[17][59] = ','; // opens 2nd door
	}
	if (ChangesArrayOne[6] == 1)
	{
		mapStorage[12][58] = '.', mapStorage[12][59] = '.', mapStorage[12][60] = '.', mapStorage[12][61] = '.', mapStorage[12][62] = '.', mapStorage[12][63] = '.', mapStorage[12][64] = '.', mapStorage[12][65] = '.', mapStorage[12][66] = '.', mapStorage[12][67] = '.', mapStorage[12][68] = '.', mapStorage[12][69] = '.', mapStorage[12][70] = '.', mapStorage[12][71] = '.', mapStorage[12][72] = '.';
		mapStorage[13][58] = '.';
		mapStorage[14][58] = '.', mapStorage[14][60] = '.', mapStorage[14][61] = '.', mapStorage[14][62] = '.', mapStorage[14][63] = '.', mapStorage[14][64] = '.', mapStorage[14][65] = '.', mapStorage[14][66] = '.', mapStorage[14][67] = '.', mapStorage[14][68] = '.', mapStorage[14][69] = '.', mapStorage[14][70] = '.', mapStorage[14][71] = '.', mapStorage[14][72] = '.';
		mapStorage[15][58] = '.', mapStorage[15][60] = '.';
		mapStorage[16][58] = '.', mapStorage[16][60] = '.'; // turns off rightmost electric floors (Coding order follows map display order)
	}
	if (ChangesArrayOne[7] == 1)
	{
		mapStorage[14][43] = ',', mapStorage[15][43] = ','; // opens 3rd door (double door)
	}
	if (ChangesArrayOne[8] == 1)
	{
		mapStorage[11][16] = ',', mapStorage[11][17] = ','; // opens 4th door (double door)
	}
	if (ChangesArrayOne[9] == 1)
	{
		mapStorage[12][2] = '.'; // removes electric floor behind moving traps
		mapStorage[13][2] = '.', mapStorage[13][5] = '.';
		mapStorage[14][5] = '.';
		mapStorage[15][5] = '.';
		mapStorage[16][2] = '.', mapStorage[16][5] = '.';
		mapStorage[17][2] = '.';
	}
	if (ChangesArrayOne[10] == 1)
	{
		mapStorage[5][39] = ',', mapStorage[6][39] = ','; // opens 5th door between electric floors (room with row of falling traps) (double door)
		for (int i = 0; i < 34; i++) {
			bTriggerFallTrap = true;
		}
	}
	if (ChangesArrayOne[11] == 1)
	{
		mapStorage[9][54] = '.', mapStorage[9][55] = '.', mapStorage[9][56] = '.', mapStorage[9][57] = '.', mapStorage[9][58] = '.', mapStorage[9][59] = '.', mapStorage[9][60] = '.', mapStorage[9][61] = '.', mapStorage[9][62] = '.', mapStorage[9][63] = '.', mapStorage[9][64] = '.', mapStorage[9][65] = '.', mapStorage[9][66] = '.', mapStorage[9][67] = '.';
		mapStorage[4][73] = '.', mapStorage[4][74] = '.', mapStorage[4][75] = '.'; // removes electric floor near row of pressure plates and infront of final door in 2nd last room
	}
	if (ChangesArrayOne[12] == 1)
	{
		mapStorage[3][74] = ',', mapStorage[3][75] = ','; // opens last door (double door)
	}
	if (ChangesArrayOne[13] == 1)
	{
		mapStorage[19][33] = 'l', mapStorage[22][33] = 'l'; //Fanswitch to disable first few fans
	}
	if (ChangesArrayOne[14] == 1)
	{
		g_eGameState = S_VICTORY;
	}
}
