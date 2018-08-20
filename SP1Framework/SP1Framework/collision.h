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

void collisionChecker(struct SGameChar &playerInfo, char map[100][100], struct SGameTrap MovingTrap[8]);
void playerKilled(struct SGameChar &playerInfo);
void newRespawnLocation(struct SGameChar &playerInfo);
void respawnAt(struct SGameChar &playerInfo);
void renderCollisionCheck(Console &g_Console);

#endif