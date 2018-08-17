#ifndef _GAME_ASSET
#define _GAME_ASSET

#include "Framework\console.h"
#include "game.h"

using namespace std;


void getMovingTrapPos(bool &bGotTrapPos, char map[100][100], struct SGameTrap MovingTrap[8]);
void renderMovingTrap(Console &g_Console, struct SGameTrap g_sMovingTrap[8]);
void movingTrap(double &trapTime, struct SGameTrap g_sMovingTrap[8]);
void fallingTrap(int &direction, double trapTime);
void renderFallingTrap(Console &g_console);

/*struct SGameTrap
{
	COORD m_cLocation;
	bool  m_bActive;
	bool m_cDirection;
};
*/




#endif