#include "levels.h"

void resetGame(struct SGameChar &playerInfo, int ChangesArrayOne[50], struct SGameTrap g_fTrap[34], bool &bGotTrapPos) {

	for (int i = 0; i < 50; i++)	// reset array
	{
		ChangesArrayOne[i] = 0;
	}
	ChangesArrayOne[14] = 0;

	playerInfo.m_iLife = 3;			// reset lives
	playerInfo.m_cLocation.X = 1;		// reset coord x
	playerInfo.m_cLocation.Y = 28;		// reset coord y
	resetTrap(bGotTrapPos,  g_fTrap);

}

void resetGame2(struct SGameChar &playerInfo) {

	playerInfo.m_iLife = 3;			// reset lives
	playerInfo.m_cLocation.X = 1;		// reset coord x
	playerInfo.m_cLocation.Y = 28;		// reset coord y
}