#ifndef _LEVELS
#define _LEVELS
#include "Framework\console.h"
#include "game.h"


using namespace std;

void levelSelect();

void resetGame(struct SGameChar &playerInfo, int ChangesArrayOne[50], struct SFallingTrap g_fTrap[38], bool &bGotTrapPos);



#endif