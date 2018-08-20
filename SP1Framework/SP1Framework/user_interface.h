#ifndef _USER_INTERFACE
#define _USER_INTERFACE

#include "Framework\console.h"
#include <sstream>
#include "game.h"
#include <fstream>

using namespace std;

void renderUI(Console &g_console, string NumberOfLives, struct SGameChar &playerInfo);
void renderLives(struct SGameChar &playerInfo, string &NumberOfLives, enum EGAMESTATES &g_eGameState);
//void renderVictoryScreen(Console g_Console, bool g_abKeyPressed);
// void renderDefeatScreen(Console &g_Console, bool g_abKeyPressed[]);

#endif