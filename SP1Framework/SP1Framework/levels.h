#ifndef _LEVELS
#define _LEVELS
#include "Framework\console.h"
#include "game.h"


using namespace std;

void resetGame(struct SGameChar &playerInfo, int ChangesArrayOne[50], struct SGameTrap g_fTrap[34], bool &bGotTrapPos);

void resetGame2(struct SGameChar &playerInfo);
#endif