#include "levels.h"

void resetGame(struct SGameChar &playerInfo, int ChangesArrayOne[50], struct SGameTrap g_fTrap[34], bool &bGotTrapPos) {

	for (int i = 0; i < 50; i++)	// reset array
	{
		ChangesArrayOne[i] = 0;
	}

	playerInfo.m_iLife = 3;				// reset lives
	playerInfo.m_cLocation.X = 1;		// reset coord x
	playerInfo.m_cLocation.Y = 4;		// reset coord y
	resetTrap(bGotTrapPos, g_fTrap);	// disable fans bool and resets traps
}

void resetGame2(struct SGameChar &playerInfo, int ChangesArrayTwo[50], bool &bGotTrapPos2) {

	for (int i = 0; i < 50; i++)
	{
		ChangesArrayTwo[i] = 0;
	}

	playerInfo.m_iLife = 3;				// reset lives
	playerInfo.m_cLocation.X = 1;		// reset coord x
	playerInfo.m_cLocation.Y = 4;		// reset coord y
	resetStalkerTrap(bGotTrapPos2);
}