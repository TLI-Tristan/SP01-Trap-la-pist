#include "GameAsset.h"


SGameTrap g_sTrap01;
SGameTrap g_fTrap01;

void initGameAsset(){
	//Saw Trap 1
	g_sTrap01.m_bActive = true;
	g_sTrap01.m_cLocation.X = 8;
	g_sTrap01.m_cLocation.Y = 18;

	//Falling Trap 1
	g_fTrap01.m_bActive = true;
	g_fTrap01.m_cLocation.X = 1;
	g_fTrap01.m_cLocation.Y = 2;
}

void movingTrap(int &direction, double trapTime) {
	//saw trap 1	
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

void fallingTrap(int &direction, double trapTime)
{
	//Falling Trap 1
	if (g_fTrap01.m_cLocation.Y == 2) {
		direction = 1;
	}
	else if (g_fTrap01.m_cLocation.Y == 11) {
		direction = 0;
	}

	if (trapTime >= 0.1) {

		g_fTrap01.m_cLocation.Y += direction;
		trapTime = 0.0;
	}
}

void renderMovingTrap(Console &g_console) {
	WORD trapColor = 0x0C;
	{
		trapColor = 0x0A;
	}
	g_console.writeToBuffer(g_sTrap01.m_cLocation, (char)6, trapColor);
}

void renderFallingTrap(Console &g_console)
{
	WORD trapColor = 0x0C;
	{
		trapColor = 0x0A;
	}
	g_console.writeToBuffer(g_fTrap01.m_cLocation, (char)4 , trapColor);
}