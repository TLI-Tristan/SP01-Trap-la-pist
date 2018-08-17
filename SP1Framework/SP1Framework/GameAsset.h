#ifndef _GAME_ASSET
#define _GAME_ASSET

#include "Framework\console.h"

using namespace std;

void initGameAsset();
void movingTrap(int &direction, double trapTime);
void renderMovingTrap(Console &g_console);
void fallingTrap(int &direction, double trapTime);
void renderFallingTrap(Console &g_console);

struct SGameTrap
{
	COORD m_cLocation;
	bool  m_bActive;
	bool m_cDirection;
};




#endif