//#include "GameAsset.h"
//
//SGameTrap g_fTrap;
//
//void getMovingTrapPos(bool &bGotTrapPos, char map[100][100], struct SGameTrap g_sMovingTrap[8]) {
//
//	int i = 0;
//	for (int k = 0; k < 30; k++) {
//
//		for (int j = 0; j < 80; j++) {
//			if (map[k][j] == 'A') {
//				g_sMovingTrap[i].m_cLocation.X = j;
//				//else {
//					g_sMovingTrap[i].m_cLocation.Y = k + 1;
//				//}
//				i++;
//
//			}
//		}
//	}
//	bGotTrapPos = true;
//}
//
//void initMovingTrap(struct SGameTrap g_sMovingTrap[8]) {
//	for (int i = 0; i < 8; i++) {
//		if(i >= 2 && i <= 4){
//			g_sMovingTrap[i].m_cDirection = 1;
//		}
//	}
//}
//
//void movingTrap(double &trapTime, struct SGameTrap g_sMovingTrap[8]) {
//
//	if (trapTime >= 0.6) {
//
//		for (int i = 0; i < 8; i++) {
//
//			if (g_sMovingTrap[i].m_cLocation.Y == 13) {
//				g_sMovingTrap[i].m_cDirection = 1;
//			}
//
//
//
//			if (i >= 2 && i <= 4) {
//				if (g_sMovingTrap[i].m_cLocation.Y == 17) {
//					g_sMovingTrap[i].m_cDirection = -1;
//				}
//			}
//			else if (g_sMovingTrap[i].m_cLocation.Y == 18) {
//				g_sMovingTrap[i].m_cDirection = -1;
//			}
//			g_sMovingTrap[i].m_cLocation.Y += g_sMovingTrap[i].m_cDirection;
//
//
//		}
//		trapTime = 0.0;
//	}
//}
//
//void renderMovingTrap(Console &g_Console, struct SGameTrap g_sMovingTrap[8]) {
//
//	WORD trapColor = 0x0C;
//	{
//		trapColor = 0x0A;
//	}
//	for (int i = 0; i < 8; i++) {
//		g_Console.writeToBuffer(g_sMovingTrap[i].m_cLocation, "A", trapColor);
//	}
//}
//
////void renderFallingTrap(Console &g_console)
////{
////	WORD trapColor = 0x0C;
////	{
////		trapColor = 0x0A;
////	}
////	g_console.writeToBuffer(g_fTrap01.m_cLocation, (char)4 , trapColor);
////}
//
//void renderCharacter(Console &g_Console, struct SGameChar playerInfo)
//{
//	// Draw the location of the character
//	WORD charColor = 0x0C;
//	if (playerInfo.m_bActive)
//	{
//		charColor = 0x0A;
//	}
//	g_Console.writeToBuffer(playerInfo.m_cLocation, (char)1, charColor);
//}
#include "GameAsset.h"

SGameTrap g_fTrap01;

void getMovingTrapPos(bool &bGotTrapPos, char map[100][100], struct SGameTrap g_sMovingTrap[8]) {

	int i = 0;
	for (int k = 0; k < 30; k++) {

		for (int j = 0; j < 80; j++) {
			if (map[k][j] == 'A') {
				g_sMovingTrap[i].m_cLocation.X = j;
				g_sMovingTrap[i].m_cLocation.Y = k + 1;
				i++;

			}
		}
	}
	bGotTrapPos = true;
}


void initMovingTrap(struct SGameTrap g_sMovingTrap[8]) {

	for (int i = 0; i < 8; i++) {

		g_sMovingTrap[i].m_cDirection = 1;
	}
}


void movingTrap(double &trapTime, struct SGameTrap g_sMovingTrap[8]) {

	if (trapTime >= 0.1) {

		for (int i = 0; i < 8; i++) {



			if (g_sMovingTrap[i].m_cLocation.Y == 13) {
				g_sMovingTrap[i].m_cDirection = 1;
			}

			if (i <= 4 && i >= 2) {
				if (g_sMovingTrap[i].m_cLocation.Y == 17) {
					g_sMovingTrap[i].m_cDirection = -1;
				}
			}
			else if (g_sMovingTrap[i].m_cLocation.Y == 18) {
				g_sMovingTrap[i].m_cDirection = -1;
			}
			g_sMovingTrap[i].m_cLocation.Y += g_sMovingTrap[i].m_cDirection;


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

void renderFallingTrap(Console &g_console)
{
	WORD trapColor = 0x0C;
	{
		trapColor = 0x0A;
	}
	g_console.writeToBuffer(g_fTrap01.m_cLocation, (char)4, trapColor);
}

void renderCharacter(Console &g_Console, struct SGameChar playerInfo)
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	if (playerInfo.m_bActive)
	{
		charColor = 0x0A;
	}
	g_Console.writeToBuffer(playerInfo.m_cLocation, (char)1, charColor);
}