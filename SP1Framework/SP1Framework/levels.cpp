#include "levels.h"

void levelSelect() {



	//switch (Choice) {
	//case 1: LevelSelected = 1; // set LevelSelected values (for hard-coding level assets)
	//	g_eGameState = S_GAME;

	//	g_sChar.m_iLife = 3;			// reset lives
	//	g_sChar.m_cLocation.X = 1;		// reset coord x
	//	g_sChar.m_cLocation.Y = 28;		// reset coord y
	//	newRespawnLocation(g_sChar);	// reset spawn

	//	for (int i = 0; i < 50; i++)	// reset array
	//	{
	//		ChangesArrayOne[i] = 0;
	//	}
	//	g_sChar.m_iLife = 3;
	//	g_sChar.m_cLocation.X = 1;
	//	g_sChar.m_cLocation.Y = 28;
	//	ChangesArrayOne[14] = 0;
	//	break;
	//case 3: g_bQuitGame = true;
	//	break;
	//}

}

void resetGame(struct SGameChar &playerInfo, int ChangesArrayOne[50], struct SFallingTrap g_fTrap[34], bool &bGotTrapPos) {

	for (int i = 0; i < 50; i++)	// reset array
	{
		ChangesArrayOne[i] = 0;
	}
	ChangesArrayOne[14] = 0;

//	trap = false;
	playerInfo.m_iLife = 3;			// reset lives
	playerInfo.m_cLocation.X = 1;		// reset coord x
	playerInfo.m_cLocation.Y = 28;		// reset coord y
	resetTrap(bGotTrapPos,  g_fTrap);

}