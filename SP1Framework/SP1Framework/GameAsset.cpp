#include "GameAsset.h"

int direction = 1;

void getMovingTrapPos(bool &bGotTrapPos, char map[100][100], struct SGameTrap g_sMovingTrap[8]) {

	int i = 0;
	for (int k = 0; k < 30; k++) {

		for (int j = 0; j < 80; j++) {
			if (map[k][j] == 'A') {
				g_sMovingTrap[i].m_cLocation.X = j;
				g_sMovingTrap[i].m_cLocation.Y = k +1;
				i++;

			}
		}
	}
	bGotTrapPos = true;
}


void movingTrap(double &trapTime, struct SGameTrap g_sMovingTrap[8]) {
	//static bool forward = true;

		/*	if (g_sMovingTrap[0].m_cLocation.Y > 13 && forward == true) {
				if (g_sMovingTrap[0].m_cLocation.Y == 19)
				{
					forward = false;
				}
					g_sMovingTrap[0].m_cLocation.Y++;
					map[g_sMovingTrap[0].m_cLocation.Y - 1][g_sMovingTrap[0].m_cLocation.X] = ' ';
					map[g_sMovingTrap[0].m_cLocation.Y][g_sMovingTrap[0].m_cLocation.X] = 'A';

			
			if (forward == false) {
				if (g_sMovingTrap[0].m_cLocation.Y >= 14)
				{
					forward = true;
				}
					g_sMovingTrap[0].m_cLocation.Y -= 1;
					map[g_sMovingTrap[0].m_cLocation.Y + 1][g_sMovingTrap[0].m_cLocation.X] = ' ';
					map[g_sMovingTrap[0].m_cLocation.Y][g_sMovingTrap[0].m_cLocation.X] = 'A';

			}
			if (map[playerInfo.m_cLocation.Y][playerInfo.m_cLocation.X] == 'A') {

				playerInfo.m_iLife -= 1;

			}*/

		//	map[g_sMovingTrap[0].m_cLocation.X][g_sMovingTrap[0].m_cLocation.Y] = 'A';
			
		//}
	if (trapTime >= 0.8) {

		for (int i = 0; i < 8; i++) {



			if (g_sMovingTrap[i].m_cLocation.Y == 13) {
				direction = 1;
			}
			else if (g_sMovingTrap[i].m_cLocation.Y == 18) {
				direction = -1;
			}
			g_sMovingTrap[i].m_cLocation.Y += direction;


		}
		trapTime = 0.0;
	}
}

void renderMovingTrap(Console &g_Console, struct SGameTrap g_sMovingTrap[8]) {

	WORD trapColor = 0x0C;
	{
		trapColor = 0x0A;
	}
	for (int i = 0; i < 8; i++) {
		g_Console.writeToBuffer(g_sMovingTrap[i].m_cLocation, "A", trapColor);
	}
}