#ifndef _COLLISION_CHECK
#define _COLLISION_CHECK

#include "game.h"
#include "Framework\console.h"

using namespace std;

struct _CollisionLocation {
	int collisionX;
	int collisionY;
	bool bCollisionCheck;
};

void collisionChecker(int LevelSelect, struct SGameChar &playerInfo, char map[100][100], struct SGameMovingTrap MovingTrap[8], struct SGameTrap FallingTrap[34], struct SGameTrap g_sDoublePivotTrap, struct SGameTrap g_sBouncingTrap);
void playerKilled(struct SGameChar &playerInfo);
void newRespawnLocation(struct SGameChar &playerInfo);
void renderCollisionCheck(Console &g_Console);


#endif