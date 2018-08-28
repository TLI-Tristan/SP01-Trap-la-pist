#include <iostream>
#include "collision.h"

bool bHitSomething = false;

void collisionChecker(int LevelSelected, struct SGameChar &playerInfo, char map[100][100], struct SGameMovingTrap MovingTrap[8], struct SGameTrap FallingTrap[34], struct SGameTrap g_sDoublePivotTrap, 
	struct SGameTrap g_sBouncingTrap, struct SGameTrap g_sStalkerTrap[7], struct SGameTrap ChargeTrap[12], struct SGameTrap g_sRandomMovementTrap[28], struct storage lineArray[100]) // check if player hit anything
{
	int Y = playerInfo.m_cLocation.Y - 1;
	int X = playerInfo.m_cLocation.X;

	if (map[Y][X] != ' ' && map[Y][X] != 'A' && map[Y][X] != 'T')
	{
		bHitSomething = true;

		 if (map[Y][X] == 'S' || map[Y][X] == '!' || map[Y][X] == 'E')
		{
			 playerKilled(playerInfo);
		}
		 else if (map[Y][X] == 'C')
		 {
			 newRespawnLocation(playerInfo);
		 }

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

		if (playerInfo.m_cLocation.X == g_sBouncingTrap.m_cLocation.X && playerInfo.m_cLocation.Y == g_sBouncingTrap.m_cLocation.Y)
		{

			bHitSomething = true;
			playerKilled(playerInfo);
		}

		for (int i = 0; i < 7; i++)
		{
			if (playerInfo.m_cLocation.X == g_sStalkerTrap[i].m_cLocation.X && playerInfo.m_cLocation.Y == g_sStalkerTrap[i].m_cLocation.Y)
			{
				bHitSomething = true;
				playerKilled(playerInfo);
			}
		}
		for (int i = 0; i < 12; i++) 
		{
			if (i <= 2) {
				if (playerInfo.m_cLocation.X == ChargeTrap[i].m_cLocation.X && playerInfo.m_cLocation.Y <= ChargeTrap[i].m_cLocation.Y && playerInfo.m_cLocation.Y >= 2)
				{
					bHitSomething = true;
					playerKilled(playerInfo);
				}
			}
			else if (i >= 5 && i <= 9) 
			{
				if (playerInfo.m_cLocation.X == ChargeTrap[i].m_cLocation.X && playerInfo.m_cLocation.Y <= ChargeTrap[i].m_cLocation.Y && playerInfo.m_cLocation.Y >= 22)
				{
					bHitSomething = true;
					playerKilled(playerInfo);
				}
			}
			else if (i >= 3 && i <= 4) 
			{
				if (playerInfo.m_cLocation.X <= ChargeTrap[i].m_cLocation.X && playerInfo.m_cLocation.X >= 34 && playerInfo.m_cLocation.Y == ChargeTrap[i].m_cLocation.Y)
				{
					bHitSomething = true;
					playerKilled(playerInfo);
				}
			}
			else if (i == 10) 
			{
				if (playerInfo.m_cLocation.X <= ChargeTrap[i].m_cLocation.X && playerInfo.m_cLocation.X >= 34 && playerInfo.m_cLocation.Y == ChargeTrap[i].m_cLocation.Y)
				{
					bHitSomething = true;
					playerKilled(playerInfo);
				}
			}

			else if (i >= 11)
			{
				if (playerInfo.m_cLocation.X <= ChargeTrap[i].m_cLocation.X && playerInfo.m_cLocation.X >= 34 && playerInfo.m_cLocation.Y == ChargeTrap[i].m_cLocation.Y)
				{
					bHitSomething = true;
					playerKilled(playerInfo);
				}
			}

		}

		for (int i = 0; i < 28; i++) 
		{
			if (playerInfo.m_cLocation.X== g_sRandomMovementTrap[i].m_cLocation.X && playerInfo.m_cLocation.Y == g_sRandomMovementTrap[i].m_cLocation.Y) 
			{
				bHitSomething = true;
				playerKilled(playerInfo);
			}
		}

		for (int i = 0; i < 100; i++) 
		{
			if (playerInfo.m_cLocation.X == lineArray[i].m_cLocation.X && playerInfo.m_cLocation.Y == lineArray[i].m_cLocation.Y) 
			{
				bHitSomething = true;
				playerKilled(playerInfo);
			}
		}


	}
}

void playerKilled(struct SGameChar &playerInfo){
	playerInfo.m_cLocation.Y = playerInfo.m_iRespawnY;
	playerInfo.m_cLocation.X = playerInfo.m_iRespawnX;
	 playerInfo.m_iLife -= 1;
	 PlaySound(TEXT("LoseALife.wav"), NULL, SND_FILENAME | SND_ASYNC);
	// resetFallingTrap();
}

void newRespawnLocation(struct SGameChar &playerInfo) {

	playerInfo.m_iRespawnY = playerInfo.m_cLocation.Y;
	playerInfo.m_iRespawnX = playerInfo.m_cLocation.X;
	PlaySound(TEXT("Checkpoint.wav"), NULL, SND_FILENAME | SND_ASYNC);

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
