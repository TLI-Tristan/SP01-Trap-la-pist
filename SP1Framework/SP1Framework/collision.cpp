#include <iostream>
#include "collision.h"
#include "game.h"

//objective : check collision every frame

// object

// collision between

// player


void collisionChecker(struct SGameChar &playerInfo, char map[100][100], bool &bHitSomething) // check if player hit anything
{
	int Y = playerInfo.m_cLocation.Y - 1;
	int X = playerInfo.m_cLocation.X;

	if (map[Y][X] != ' ') 
	{
		bHitSomething = true;

		//if (map[Y][X] == '#') {

		//}
		 if (map[Y][X] == 'S' || map[Y][X] == '!' || map[Y][X] == 'E')
		{
			 playerKilled(playerInfo);
			 respawnAt(playerInfo);

		}
		 else if (map[Y][X] == 'C')
		 {
			 newRespawnLocation(playerInfo);
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
		
		//else if (map[Y][X] == 'G')
		//{

		//}
	}
}



void playerKilled(struct SGameChar &playerInfo){
     playerInfo.m_cLocation.X = 1;
	 playerInfo.m_cLocation.Y = 28;
	 playerInfo.m_iLife -= 1;
}

void newRespawnLocation(struct SGameChar &playerInfo) {

	playerInfo.m_iRespawnY = playerInfo.m_cLocation.Y;
	playerInfo.m_iRespawnX = playerInfo.m_cLocation.X;

}

void respawnAt(struct SGameChar &playerInfo) {

	playerInfo.m_cLocation.Y = playerInfo.m_iRespawnY;
	playerInfo.m_cLocation.X = playerInfo.m_iRespawnX;
}
