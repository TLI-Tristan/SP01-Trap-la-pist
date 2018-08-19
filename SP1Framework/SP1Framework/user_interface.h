#ifndef _USER_INTERFACE
#define _USER_INTERFACE

#include "Framework\console.h"
#include <sstream>
#include "game.h"

using namespace std;

void renderUI(Console &g_console, string NumberOfLives, struct SGameChar &playerInfo);
void renderLives(struct SGameChar &playerInfo, string &NumberOfLives, enum EGAMESTATES &g_eGameState);



#endif