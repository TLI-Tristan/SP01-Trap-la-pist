#include "GameAsset.h"


SGameTrap g_sTrap01;


void initGameAsset(){

	g_sTrap01.m_bActive = true;
	g_sTrap01.m_cLocation.X = 8;
	g_sTrap01.m_cLocation.Y = 18;

}

void movingTrap(int &direction, double trapTime) {

	if (g_sTrap01.m_cLocation.Y == 13) {
		direction = 1;
	}
	else if (g_sTrap01.m_cLocation.Y == 18) {
		direction = -1;
	}

	if (trapTime >= 0.1) {

		g_sTrap01.m_cLocation.Y += direction;
		trapTime = 0.0;
	}

}

void renderMovingTrap(Console &g_Console) {
	WORD trapColor = 0x0C;
	{
		trapColor = 0x0A;
	}
	g_Console.writeToBuffer(g_sTrap01.m_cLocation, (char)1, trapColor);

}