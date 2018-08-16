#ifndef _COLLISION_CHECK
#define _COLLISION_CHECK


using namespace std;

struct _CollisionLocation {
	int collisionX;
	int collisionY;
	bool bCollisionCheck;
};

void collisionChecker(struct SGameChar &playerInfo, char map[100][100], bool &bHitSomething, int &DeathCount);
void playerKilled(int &DeathCount, struct SGameChar &playerInfo);

#endif