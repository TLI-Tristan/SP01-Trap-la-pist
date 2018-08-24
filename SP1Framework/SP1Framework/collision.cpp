#include <iostream>
#include "collision.h"

bool bHitSomething = false;

void collisionChecker(int LevelSelected, struct SGameChar &playerInfo, char map[100][100], struct SGameMovingTrap MovingTrap[8], struct SGameTrap FallingTrap[34], struct SGameTrap g_sDoublePivotTrap, struct SGameTrap g_sBouncingTrap) // check if player hit anything
{
	int Y = playerInfo.m_cLocation.Y - 1;
	int X = playerInfo.m_cLocation.X;

	if (map[Y][X] != ' ' && map[Y][X] != 'A' && map[Y][X] != 'T')
	{
		bHitSomething = true;

		//if (map[Y][X] == '#') {

		//}
		 if (map[Y][X] == 'S' || map[Y][X] == '!' || map[Y][X] == 'E')
		{
			 playerKilled(playerInfo);
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
	if (LevelSelected == 1) 
	{
		for (int i = 0; i < 8; i++) {
			if (playerInfo.m_cLocation.X == MovingTrap[i].m_cLocation.X && playerInfo.m_cLocation.Y == MovingTrap[i].m_cLocation.Y)
			{
				bHitSomething = true;
				playerKilled(playerInfo);
			}
		}
		for (int i = 0; i < 34; i++) {
			if (playerInfo.m_cLocation.X == FallingTrap[i].m_cLocation.X && playerInfo.m_cLocation.Y == FallingTrap[i].m_cLocation.Y)
			{

				bHitSomething = true;
				playerKilled(playerInfo);
			}
		}
	}
	else if (LevelSelected == 2)
	{

		if (playerInfo.m_cLocation.X == g_sDoublePivotTrap.m_cLocation.X && playerInfo.m_cLocation.Y == g_sDoublePivotTrap.m_cLocation.Y)
		{
			bHitSomething = true;
			playerKilled(playerInfo);
		}

		if (playerInfo.m_cLocation.X == g_sDoublePivotTrap.m_cLocation.X && playerInfo.m_cLocation.Y == g_sBouncingTrap.m_cLocation.Y)
		{

			bHitSomething = true;
			playerKilled(playerInfo);
		}
	}

}



void playerKilled(struct SGameChar &playerInfo){
	playerInfo.m_cLocation.Y = playerInfo.m_iRespawnY;
	playerInfo.m_cLocation.X = playerInfo.m_iRespawnX;
	 playerInfo.m_iLife -= 1;
	// resetFallingTrap();
}

void newRespawnLocation(struct SGameChar &playerInfo) {

	playerInfo.m_iRespawnY = playerInfo.m_cLocation.Y;
	playerInfo.m_iRespawnX = playerInfo.m_cLocation.X;

}

void renderCollisionCheck(Console &g_Console) {

	COORD c;
	c.X = g_Console.getConsoleSize().X + 80;
	c.Y = 0;

	if (bHitSomething == false) {
		g_Console.writeToBuffer(c, "No collision", 0xC);
	}
	if (bHitSomething == true) {

		g_Console.writeToBuffer(c, "COLLISION DETECTED", 0xC);
		bHitSomething = false;

	}
}
