#include <iostream>
#include "collisioncheck.h"
#include "game.h"

//objective : check collision every frame

// object

// collision between

// player


void collisionChecker(struct SGameChar &playerInfo, char map[100][100], bool &bHitSomething, int &DeathCount) // check if player hit anything
{
	int Y = playerInfo.m_cLocation.Y - 1;
	int X = playerInfo.m_cLocation.X;

	if (map[Y][X] != ' ') 
	{
		bHitSomething = true;

		//if (map[Y][X] == '#') {

		//}
		 if (map[Y][X] == 'S')
		{
			 playerKilled(*&DeathCount, *&playerInfo);
		}
		//else if (map[Y][X] == 'D')
		//{

		//}
		//else if (map[Y][X] == 'E')
		//{

		//}
		//else if (map[Y][X] == 'P')
		//{

		//}
		//else if (map[Y][X] == 'Z' || map[Y][X] == 'X' || map[Y][X] == 'N' || map[Y][X] == 'M')
		//{

		//}
		//else if (map[Y][X] == 'T')
		//{

		//}
		//else if (map[Y][X] == 'A')
		//{

		//}
		//else if (map[Y][X] == 'W')
		//{

		//}
		//else if (map[Y][X] == 'C')
		//{

		//}
		//else if (map[Y][X] == 'G')
		//{

		//}
	}
}



void playerKilled(int &DeathCount, struct SGameChar &playerInfo){
	DeathCount++;
	playerInfo.m_cLocation.X = 1;
	playerInfo.m_cLocation.Y = 28;
}

/*
void RespawnAt()
{
	g_sChar.m_cLocation.X = NewX;
	g_sChar.m_cLocation.Y = NewY;
}*/