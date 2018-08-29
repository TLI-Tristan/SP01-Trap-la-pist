#include "GameAsset.h"


bool bTriggerFallTrap = false;
bool disableFans = false;

storage ChargeTrapStorage[12];
storage2 randomMovementTrapStorage[28];

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

				g_sDoublePiovtTrap.m_cLocation.X = 37;
				g_sDoublePiovtTrap.m_cLocation.Y = 22;
}

void getStalkerTrapPos(char map[100][100], struct SGameTrap g_sStalkerTrap[7])
{
	int i = 0;
	for (int k = 0; k < 30; k++)
	{
		for (int j = 0; j < 80; j++)
		{
			if (map[k][j] == 'U')
			{
				g_sStalkerTrap[i].m_cLocation.X = j;
				g_sStalkerTrap[i].m_cLocation.Y = k + 1;
				i++;
			}
		}
	}
}

void getChargeTrapPos(char map[100][100], struct SGameTrap g_sMovingTrap[12])
{

	int i = 0;
	for (int k = 0; k<30; k++)
	{
		for (int j = 0; j<80; j++)
		{
			if (map[k][j] == 'Y' || map[k][j] == 'y')
			{
				g_sMovingTrap[i].m_cLocation.X = j;
				g_sMovingTrap[i].m_cLocation.Y = k + 1;
				i++;
			}
		}
	}

}

void getFanTrapPos(char map[100][100], struct SGameTrap g_leftFanTrap[5], struct SGameTrap g_rightFanTrap[5], struct SGameTrap g_upFanTrap[5], struct SGameTrap g_downFanTrap[5])
{
	int i = 0, h = 0, g = 0, f = 0;
	for (int k = 0; k < 30; k++)
	{
		for (int j = 0; j < 80; j++)
		{
			if (map[k][j] == 'Z')
			{
				g_upFanTrap[i].m_cLocation.X = j;
				g_upFanTrap[i].m_cLocation.Y = k + 1;
				i++;
			}
			else if (map[k][j] == 'X')
			{
				g_downFanTrap[h].m_cLocation.X = j;
				g_downFanTrap[h].m_cLocation.Y = k + 1;
				h++;
			}
			else if (map[k][j] == 'N')
			{
				if (disableFans == false)
				{
					g_leftFanTrap[g].m_cLocation.X = j;
					g_leftFanTrap[g].m_cLocation.Y = k + 1;
					g++;
				}
			}
			else if (map[k][j] == 'M')
			{
				g_rightFanTrap[f].m_cLocation.X = j;
				g_rightFanTrap[f].m_cLocation.Y = k + 1;
				f++;
			}
		}
	}
}

void getRandomMovementTrapPos(char map[100][100], struct SGameTrap g_sRandomMovementTrap[28]) {

	int i = 0;
	for (int k = 0; k < 30;  k++) 
	{
		for (int j = 0; j < 80; j++) {
			if (map[k][j] == 'R') {
				g_sRandomMovementTrap[i].m_cLocation.X = j;
				g_sRandomMovementTrap[i].m_cLocation.Y = k + 1;
				i++;
			}
		}
	}

	for (int i = 0; i < 28; i++) {

		randomMovementTrapStorage[i].m_cOne.X = g_sRandomMovementTrap[i].m_cLocation.X;
		randomMovementTrapStorage[i].m_cOne.Y = g_sRandomMovementTrap[i].m_cLocation.Y;

		randomMovementTrapStorage[i].m_cTwo.X = g_sRandomMovementTrap[i].m_cLocation.X + 2;
		randomMovementTrapStorage[i].m_cTwo.Y = g_sRandomMovementTrap[i].m_cLocation.Y;

		randomMovementTrapStorage[i].m_cThree.X = g_sRandomMovementTrap[i].m_cLocation.X;
		randomMovementTrapStorage[i].m_cThree.Y = g_sRandomMovementTrap[i].m_cLocation.Y - 2;

		randomMovementTrapStorage[i].m_cFour.X = g_sRandomMovementTrap[i].m_cLocation.X + 2;
		randomMovementTrapStorage[i].m_cFour.Y = g_sRandomMovementTrap[i].m_cLocation.Y - 2;

		randomMovementTrapStorage[i].num = 1;
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

void fallingTrap(double &ftrapTime, struct SGameTrap g_fTrap[34])
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

void doublePivotTrap(double &trapTime, struct SGameTrap &g_sDoublePiovtTrap, double &trapTime2) {

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


int bT_x = 1;
int bT_y = 1;
int p = 0;

void bouncingTrap(double &g_dBouncingTrap, struct SGameTrap &g_sBouncingTrap, struct storage lineArray[100]) {

	if (g_dBouncingTrap >= 0.02) {

		if (g_sBouncingTrap.m_cLocation.X == 78) {

			bT_x *= -1;
			resetLineArray(lineArray);
		}
		else if (g_sBouncingTrap.m_cLocation.X == 1) {

			bT_x *= -1;
			resetLineArray(lineArray);
		}

		if (g_sBouncingTrap.m_cLocation.Y == 28) {

			bT_y *= -1;
			resetLineArray(lineArray);
		}
		else if (g_sBouncingTrap.m_cLocation.Y == 2) {
			bT_y *= -1;
			resetLineArray(lineArray);
		}

		lineArray[p].m_cLocation.X = g_sBouncingTrap.m_cLocation.X;
		lineArray[p].m_cLocation.Y = g_sBouncingTrap.m_cLocation.Y;
		p++;

		g_sBouncingTrap.m_cLocation.X += bT_x;
		g_sBouncingTrap.m_cLocation.Y += bT_y;

		g_dBouncingTrap = 0.0;
	}



}

void resetLineArray(struct storage lineArray[100]) {

	for (int i = 0; i < 100; i++) {
		lineArray[i].m_cLocation.X = NULL;
		lineArray[i].m_cLocation.Y = NULL;
	}
	p = 0;
}

std::random_device rd; // truly random number generator
std::mt19937 eng(rd()); 
std::uniform_int_distribution<> distr(1, 4); 

int compare[28];
	
void randomMovementTrap(double &trapTime, struct SGameTrap g_sRandomMovementTrap[28]) {

	if (trapTime >= 0.7) {

		for (int i = 0; i < 28; i++) {
			int randomNumber;

			do {								//get a random number to set a random position
				randomNumber = distr(eng);

			} while (randomNumber == randomMovementTrapStorage[i].num);


			if (randomNumber == 1) {

				g_sRandomMovementTrap[i].m_cLocation.X = randomMovementTrapStorage[i].m_cOne.X;
				g_sRandomMovementTrap[i].m_cLocation.Y = randomMovementTrapStorage[i].m_cOne.Y;
			}
			else if (randomNumber == 2) {

				g_sRandomMovementTrap[i].m_cLocation.X = randomMovementTrapStorage[i].m_cTwo.X;
				g_sRandomMovementTrap[i].m_cLocation.Y = randomMovementTrapStorage[i].m_cTwo.Y;

			}
			else if (randomNumber == 3) {

				g_sRandomMovementTrap[i].m_cLocation.X = randomMovementTrapStorage[i].m_cThree.X;
				g_sRandomMovementTrap[i].m_cLocation.Y = randomMovementTrapStorage[i].m_cThree.Y;

			}
			else if (randomNumber == 4) {

				g_sRandomMovementTrap[i].m_cLocation.X = randomMovementTrapStorage[i].m_cFour.X;
				g_sRandomMovementTrap[i].m_cLocation.Y = randomMovementTrapStorage[i].m_cFour.Y;

			}
			randomMovementTrapStorage[i].num = randomNumber;
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
	disableFans = false;
}

void resetTrap2(bool &bGotTrapPos2)
{
	bGotTrapPos2 = false;
	rotation = 1;
	rotation2 = 1;
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

int numberprint[12] = { 6,6,6,5,5,7,7,7,7,7,5,9 };

void chargeTrap(double & trapTime, SGameTrap g_sChargeTrap[12])
{
	if (trapTime >= 0.35) {
		for (int i = 0; i < 12; i++)
		{
			if (i <= 2)
			{
				if (g_sChargeTrap[i].m_cLocation.Y == 2)
				{
					g_sChargeTrap[i].m_cLocation.Y += 5;
					numberprint[i] = 6;
				}
				else {
					g_sChargeTrap[i].m_cLocation.Y -= 1;
					numberprint[i]--;
				}
			}

			else if (i >= 5 && i <= 9)
			{
				if (g_sChargeTrap[i].m_cLocation.Y == 22)
				{
					g_sChargeTrap[i].m_cLocation.Y += 6;
					numberprint[i] = 7;
				}
				else {
					g_sChargeTrap[i].m_cLocation.Y -= 1;
					numberprint[i]--;
				}
			}
			else if (i >= 3 && i <= 4)
			{
				if (g_sChargeTrap[i].m_cLocation.X == 34)
				{
					g_sChargeTrap[i].m_cLocation.X += 4;
					numberprint[i] = 5;
				}
				else {
					g_sChargeTrap[i].m_cLocation.X -= 1;
					numberprint[i]--;
				}
			}
			else if (i == 10)
			{
				if (g_sChargeTrap[i].m_cLocation.X == 34)
				{
					g_sChargeTrap[i].m_cLocation.X += 4;
					numberprint[i] = 5;
				}
				else {
					g_sChargeTrap[i].m_cLocation.X -= 1;
					numberprint[i]--;
				}
			}
			else if (i >= 11)
			{
				if (g_sChargeTrap[i].m_cLocation.X == 34)
				{
					g_sChargeTrap[i].m_cLocation.X += 8;
					numberprint[i] = 9;
				}
				else {
					g_sChargeTrap[i].m_cLocation.X -= 1;
					numberprint[i]--;
				}
			}
			trapTime = 0.0;
		}
	}

	for (int i = 0; i < 12; i++)
	{
		ChargeTrapStorage[i].m_cLocation.X = g_sChargeTrap[i].m_cLocation.X;
		ChargeTrapStorage[i].m_cLocation.Y = g_sChargeTrap[i].m_cLocation.Y;
	}

}

void renderChargeTrap(Console &g_Console, struct SGameTrap g_sChargeTrap[12])
{

	WORD trapColor = 0x0C;
	{
		trapColor = 0x0A;
	}

	for (int i = 0; i < 12; i++) {

		if (i <= 2) {
			for (int p = 0; p < numberprint[i]; p++) {

				g_Console.writeToBuffer(ChargeTrapStorage[i].m_cLocation, "Y", trapColor);
				ChargeTrapStorage[i].m_cLocation.Y -= 1;

			}
		}
		else if (i >= 5 && i <= 9) {
			for (int a = 0; a < numberprint[i]; a++)
			{

				g_Console.writeToBuffer(ChargeTrapStorage[i].m_cLocation, "Y", trapColor);
				ChargeTrapStorage[i].m_cLocation.Y -= 1;
			}

		}
		else if (i >= 3 && i <= 4) {
			for (int b = 0; b < numberprint[i]; b++)
			{
				g_Console.writeToBuffer(ChargeTrapStorage[i].m_cLocation, "Y", trapColor);
				ChargeTrapStorage[i].m_cLocation.X -= 1;
			}
		}
		else if (i == 10) {
			for (int c = 0; c < numberprint[i]; c++)
			{
				g_Console.writeToBuffer(ChargeTrapStorage[i].m_cLocation, "Y", trapColor);
				ChargeTrapStorage[i].m_cLocation.X -= 1;
			}
		}
		else if (i >= 11) {
			for (int d = 0; d < numberprint[i]; d++)
			{
				g_Console.writeToBuffer(ChargeTrapStorage[i].m_cLocation, "Y", trapColor);
				ChargeTrapStorage[i].m_cLocation.X -= 1;

			}
		}
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

void renderBouncingTrap(Console &g_Console, struct SGameTrap g_sBouncingTrap, struct storage lineArray[100]) {

	WORD trapColor = 0x0C;
	{
		trapColor = 0x0A;
	}

	for (int i = 0; i < 100; i++) {

		g_Console.writeToBuffer(lineArray[i].m_cLocation, "9", trapColor);
	}
	g_Console.writeToBuffer(g_sBouncingTrap.m_cLocation, "9", trapColor);
}

void renderStalkerTrap(Console &g_Console, struct SGameTrap g_sStalkerTrap[7]) {

	WORD trapColor = 0x0C;
	{
		trapColor = 0x0D;
	}
	for (int i = 0; i < 7; i++) {

		if (g_sStalkerTrap[i].m_bActive == true) {
			g_Console.writeToBuffer(g_sStalkerTrap[i].m_cLocation, "U", 0x0F);
		}
		else {
			g_Console.writeToBuffer(g_sStalkerTrap[i].m_cLocation, "U", trapColor);
		}
	}
}

void renderRandomMvementTrap(Console &g_Console, struct SGameTrap g_sRandomMovementTrap[28]) {

	WORD trapColor = 0x0C;
	{
		trapColor = 0x0E;
	}
	for (int i = 0; i < 28; i++) {
		g_Console.writeToBuffer(g_sRandomMovementTrap[i].m_cLocation, "R", trapColor);
	}

}

void renderCharacter(Console &g_Console, struct SGameChar playerInfo)
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	if (playerInfo.m_bActive)
	{
		charColor = 0x0F;
	}
	g_Console.writeToBuffer(playerInfo.m_cLocation, (char)1, charColor);
}


// START FAN FUNCTION //
double FanDelay = 0.1; // can be edited
int FanRange = 28;
void FanFunctionMain(struct SGameChar &playerInfo, char mapStorage[100][100], Console &g_console, struct SGameTrap g_leftFanTrap[5], struct SGameTrap g_rightFanTrap[5], struct SGameTrap g_upFanTrap[5], struct SGameTrap g_downFanTrap[5])
{
	for (int i = 0; i < 5; i++)
	{
		// left fan checking
		g_leftFanTrap[i].m_bActive = false;
		bool gotWallleft = false;
		for (int m = 0; m < FanRange; m++)
		{
			for (int r = 0; r < FanRange; r++)
			{
				if (playerInfo.m_cLocation.X + r < g_leftFanTrap[i].m_cLocation.X) // checks row of x-axis, and checks area before trap
				{
					if (mapStorage[playerInfo.m_cLocation.Y - 1][playerInfo.m_cLocation.X + r] == '#') // check whether there is a wall infront of trap
					{
						gotWallleft = true;
					}
				}
			}
	
			if (gotWallleft == false && playerInfo.m_cLocation.Y == (int)g_leftFanTrap[i].m_cLocation.Y && playerInfo.m_cLocation.X == (int)g_leftFanTrap[i].m_cLocation.X - m) // check if walls, if yes, dont activate // another loop that checks for walls in bbetween
			{
				g_leftFanTrap[i].m_bActive = true; // if player is same y level as trap, and <<Range>> away from trap, make it active
			}
		}

		// right fan checking
		g_rightFanTrap[i].m_bActive = false;
		bool gotWallright = false;

		for (int m = 0; m < FanRange; m++)
		{
			for (int r = 0; r < FanRange; r++)
			{
				if (playerInfo.m_cLocation.X - r > g_rightFanTrap[i].m_cLocation.X) // checks row of x-axis, and checks area before trap
				{
					if (mapStorage[playerInfo.m_cLocation.Y - 1][playerInfo.m_cLocation.X - r] == '#') // check whether there is a wall infront of trap
					{
						gotWallright = true;
					}
				}
			}
			if (gotWallright == false && playerInfo.m_cLocation.Y == (int)g_rightFanTrap[i].m_cLocation.Y && playerInfo.m_cLocation.X == (int)g_rightFanTrap[i].m_cLocation.X + m)
			{
				g_rightFanTrap[i].m_bActive = true;
			}
		}

		// up fan chekcking
		g_upFanTrap[i].m_bActive = false;
		bool gotWallup = false;
		for (int n = 0; n < FanRange; n++)
		{
			for (int r = 0; r < FanRange; r++)
			{
				if (playerInfo.m_cLocation.Y - 1 + r < g_upFanTrap[i].m_cLocation.Y) // checks col of y-axis, and checks area before trap
				{
					if (mapStorage[playerInfo.m_cLocation.Y - 1 + r][playerInfo.m_cLocation.X] == '#') // check whether there is a wall infront of trap
					{
						gotWallup = true;
					}
				}
			}
			if (gotWallup == false && playerInfo.m_cLocation.Y == (int)g_upFanTrap[i].m_cLocation.Y - n && playerInfo.m_cLocation.X == (int)g_upFanTrap[i].m_cLocation.X)
			{
				g_upFanTrap[i].m_bActive = true;
			}
		}

		// down fan checking
		g_downFanTrap[i].m_bActive = false;
		bool gotWalldown = false;
		for (int n = 0; n < FanRange; n++)
		{
			for (int r = 0; r < FanRange; r++)
			{
				if (playerInfo.m_cLocation.Y - 1 - r > g_downFanTrap[i].m_cLocation.Y) // checks col of y-axis, and checks area before trap
				{
					if (mapStorage[playerInfo.m_cLocation.Y - 1 - r][playerInfo.m_cLocation.X] == '#') // check whether there is a wall infront of trap
					{
						gotWalldown = true;
					}
				}
			}
			if (gotWalldown == false && playerInfo.m_cLocation.Y == (int)g_downFanTrap[i].m_cLocation.Y + n && playerInfo.m_cLocation.X == (int)g_downFanTrap[i].m_cLocation.X)
			{
				g_downFanTrap[i].m_bActive = true;
			}
		}
	}
}

void leftFanMovement(double &leftFanTrapTime, struct SGameChar &playerInfo, char mapStorage[100][100], SGameTrap g_leftFanTrap[5])
{
	if (leftFanTrapTime >= FanDelay && disableFans == false)
	{
		for (int i = 0; i < 5; i++)
		{
			if (g_leftFanTrap[i].m_bActive == true && (mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X - 1] != '#' && mapStorage[(int)playerInfo.m_cLocation.Y - 2][(int)playerInfo.m_cLocation.X] != 'D') )
			{
				playerInfo.m_cLocation.X--;
			}
		}
		leftFanTrapTime = 0.0;
	}
}

void rightFanMovement(double &rightFanTrapTime, struct SGameChar &playerInfo, char mapStorage[100][100], SGameTrap g_rightFanTrap[5])
{
	if (rightFanTrapTime >= FanDelay)
	{
		for (int i = 0; i < 5; i++)
		{
			if (g_rightFanTrap[i].m_bActive == true && (mapStorage[(int)playerInfo.m_cLocation.Y - 1][(int)playerInfo.m_cLocation.X + 1] != '#' && mapStorage[(int)playerInfo.m_cLocation.Y - 2][(int)playerInfo.m_cLocation.X] != 'D') )
			{
				playerInfo.m_cLocation.X++;
			}
		}
		rightFanTrapTime = 0.0;

	}
}

void upFanMovement(double &upFanTrapTime, struct SGameChar &playerInfo, char mapStorage[100][100], SGameTrap g_upFanTrap[5])
{
	if (upFanTrapTime >= FanDelay)
	{
		for (int i = 0; i < 5; i++)
		{
			if (g_upFanTrap[i].m_bActive == true && (mapStorage[(int)playerInfo.m_cLocation.Y - 2][(int)playerInfo.m_cLocation.X] != '#' && mapStorage[(int)playerInfo.m_cLocation.Y - 2][(int)playerInfo.m_cLocation.X] != 'D') )
			{
				playerInfo.m_cLocation.Y--;
			}
		}
		upFanTrapTime = 0.0;

	}
}

void downFanMovement(double &downFanTrapTime, struct SGameChar &playerInfo, char mapStorage[100][100], SGameTrap g_downFanTrap[5])
{
	if (downFanTrapTime >= FanDelay)
	{
		for (int i = 0; i < 5; i++)
		{
			if (g_downFanTrap[i].m_bActive == true && (mapStorage[(int)playerInfo.m_cLocation.Y][(int)playerInfo.m_cLocation.X] != '#' && mapStorage[(int)playerInfo.m_cLocation.Y - 2][(int)playerInfo.m_cLocation.X] != 'D') )
			{
				playerInfo.m_cLocation.Y++;
			}
		}
		downFanTrapTime = 0.0;

	}
}
// END FAN FUNCTION //


int StalkerRange = 7; // (Actual Radius = StalkerRange - 1) = 6

void StalkerFunctionMain(struct SGameChar &playerInfo, char mapStorage[100][100], SGameTrap g_sStalkerTrap[7])
{
	for (int i = 0; i < 7; i++)
	{
		g_sStalkerTrap[i].m_bActive = false; // reset trap to not active

		for (int m = 0; m < StalkerRange; m++)
		{
			if (g_sStalkerTrap[i].m_bActive != true)
			{
				if ((int)playerInfo.m_cLocation.X == g_sStalkerTrap[i].m_cLocation.X - m) // check if player is left of trap by X chars range
				{
					for (int n = 0; n < StalkerRange; n++)
					{
						if ((int)playerInfo.m_cLocation.Y - 1 == g_sStalkerTrap[i].m_cLocation.Y - n - 1) // check if player is up of trap in X chars range
						{
							g_sStalkerTrap[i].m_bActive = true;
						}
						else if ((int)playerInfo.m_cLocation.Y - 1 == g_sStalkerTrap[i].m_cLocation.Y + n - 1) // check if player is down of trap in X chars range
						{
							g_sStalkerTrap[i].m_bActive = true;
						}
					}
				}
				else if ((int)playerInfo.m_cLocation.X == g_sStalkerTrap[i].m_cLocation.X + m) // check if player is right of trap by X chars range
				{
					for (int n = 0; n < StalkerRange; n++)
					{
						if ((int)playerInfo.m_cLocation.Y - 1 == g_sStalkerTrap[i].m_cLocation.Y - n - 1) // check if player is up of trap in X chars range
						{
							g_sStalkerTrap[i].m_bActive = true;
						}
						else if ((int)playerInfo.m_cLocation.Y - 1 == g_sStalkerTrap[i].m_cLocation.Y + n - 1) // check if player is down of trap in X chars range
						{
							g_sStalkerTrap[i].m_bActive = true;
						}
					}
				}
			}
		}
	}
}

void StalkerFunctionMovement(double &sTrapTime, struct SGameChar &playerInfo, char mapStorage[100][100], SGameTrap g_sStalkerTrap[7])
{
	if (sTrapTime >= 0.7) // adjust speed of trap movement 
	{
			for (int i = 0; i < 7; i++)
			{
				if (g_sStalkerTrap[i].m_bActive == true && (int)playerInfo.m_cLocation.Y != g_sStalkerTrap[i].m_cLocation.Y)  // move in y-axis first
				{
					if ((int)playerInfo.m_cLocation.Y < g_sStalkerTrap[i].m_cLocation.Y) // Player up of trap
					{
						g_sStalkerTrap[i].m_cLocation.Y--;
					}
					else if ((int)playerInfo.m_cLocation.Y > g_sStalkerTrap[i].m_cLocation.Y) // Player down of trap
					{
						g_sStalkerTrap[i].m_cLocation.Y++;
					}
				}

				else if (g_sStalkerTrap[i].m_bActive == true && (int)playerInfo.m_cLocation.X != g_sStalkerTrap[i].m_cLocation.X) // then if y-axis is same as player, move in x-axis
				{
					if ((int)playerInfo.m_cLocation.X < g_sStalkerTrap[i].m_cLocation.X) // Player left of trap
					{
						g_sStalkerTrap[i].m_cLocation.X--;
					}
					if ((int)playerInfo.m_cLocation.X > g_sStalkerTrap[i].m_cLocation.X) // Player right of trap
					{
						g_sStalkerTrap[i].m_cLocation.X++;
					}
				}
			}
			sTrapTime = 0.0;
	}		
}
	


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
	if ((int)playerInfo.m_cLocation.Y - 1 == 27 && (int)playerInfo.m_cLocation.X == 26) // 1st 2 Fans switch
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
		disableFans = true;
	}
	if (ChangesArrayOne[14] == 1)
	{
		g_eGameState = S_VICTORY;
	}
}

void ArrayLevelTwoDetect(struct SGameChar &playerInfo, int ChangesArrayTwo[50])
{
	if ((int)playerInfo.m_cLocation.Y - 1 == 14 && (int)playerInfo.m_cLocation.X == 3) // 1st Door Plate (2nd Room)
	{
		ChangesArrayTwo[0] = 1;
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 4 && (int)playerInfo.m_cLocation.X == 41) // 2nd Door Plate (4th Room/Corridor)
	{
		ChangesArrayTwo[1] = 1;
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 1 && (int)playerInfo.m_cLocation.X == 78) // 3nd Door Plate (5th Room)
	{
		ChangesArrayTwo[2] = 1;
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 24 && (int)playerInfo.m_cLocation.X == 78) // 2nd Door Plate (7th Room)
	{
		ChangesArrayTwo[3] = 1;
	}
	if ((int)playerInfo.m_cLocation.Y - 1 == 14 && (int)playerInfo.m_cLocation.X == 36) // Win
	{
		ChangesArrayTwo[4] = 1;
	}
}

void ArrayLevelTwoActivate(struct SGameChar &playerInfo, int ChangesArrayTwo[50], char mapStorage[100][100], enum EGAMESTATES &g_eGameState)
{
	if (ChangesArrayTwo[0] == 1)
	{
		mapStorage[7][11] = ','; // opens 1st door (double door)
		mapStorage[7][12] = ',';
	}
	if (ChangesArrayTwo[1] == 1)
	{
		mapStorage[1][42] = ','; // opens 2nd door
	}
	if (ChangesArrayTwo[2] == 1)
	{
		mapStorage[11][58] = ','; // opens 3rd door (double door)
		mapStorage[11][59] = ',';
	}
	if (ChangesArrayTwo[3] == 1)
	{
		mapStorage[27][43] = ','; // opens 2nd door
	}
	if (ChangesArrayTwo[4] == 1)
	{
		g_eGameState = S_VICTORY; // win
	}
}