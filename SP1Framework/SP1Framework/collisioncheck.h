#ifndef _COLLISION_CHECK
#define _COLLISION_CHECK


using namespace std;

struct _CollisionLocation {
	int collisionX;
	int collisionY;
	bool bCollisionCheck;
};

void collisionChecker(struct SGameChar &playerInfo);


#endif