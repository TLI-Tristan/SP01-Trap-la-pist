#include "user_interface.h"

void renderUI(Console &g_Console, string NumberOfLives, struct SGameChar &playerInfo) //For level 1
{
	COORD c;
	std::ostringstream ss;
	//Displays the Level at the Right
	ss.str("");
	ss << "Stage: " << "<<" << "1" << ">>"; //Change to Level with buttons
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0xC);

	//Displays Lives at the Right
	ss.str("");
	ss << "Lives: " << NumberOfLives; //Change to Number of Lives
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 1;
	g_Console.writeToBuffer(c, ss.str(), 0xC);

	//Displays Difficulty at the Right
	ss.str("");
	ss << "Difficulty: " << "Easy"; //Change to Difficulty
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 2;
	g_Console.writeToBuffer(c, ss.str(), 0xC);

	//Displays Legend at the Right
	ss.str("");
	ss << "Legend:"; //Add boxes
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 4;
	g_Console.writeToBuffer(c, ss.str(), 0xE0);

	//Displays Legends1 at the Right
	ss.str("");
	ss << "#";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 5;
	g_Console.writeToBuffer(c, ss.str(), 0x88);
	ss.str(" - Walls");
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 5;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends2 at the Right
	ss.str("");
	ss << (char)2 << " - Character";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 6;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends3 at the Right
	ss.str("");
	ss << "F";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 7;
	g_Console.writeToBuffer(c, ss.str(), 0xE0);
	ss.str("");
	ss << " - Fan";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 7;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends4 at the Right
	ss.str("");
	ss << "W";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 8;
	g_Console.writeToBuffer(c, ss.str(), 0x35);
	ss.str("");
	ss << " - Fan Switch";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 8;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends5 at the Right
	ss.str("");
	ss << "S";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 9;
	g_Console.writeToBuffer(c, ss.str(), 0x40);
	ss.str("");
	ss << " - Spike";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 9;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends6 at the Right
	ss.str("");
	ss << "A";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 10;
	g_Console.writeToBuffer(c, ss.str(), 0x02);
	ss.str("");
	ss << " - Saw Trap";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 10;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends7 at the Right
	ss.str("");
	ss << "T";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 11;
	g_Console.writeToBuffer(c, ss.str(), 0x30);
	ss.str("");
	ss << " - Falling Trap";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 11;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends8 at the Right
	ss.str("");
	ss << "G";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 12;
	g_Console.writeToBuffer(c, ss.str(), 0xE0);
	ss.str("");
	ss << " - Generator";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 12;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends9 at the Right
	ss.str("");
	ss << "E";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 13;
	g_Console.writeToBuffer(c, ss.str(), 0xC0);
	ss.str("");
	ss << " - Electric Floor";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 13;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends10 at the Right
	ss.str("");
	ss << "P";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 14;
	g_Console.writeToBuffer(c, ss.str(), 0x21);
	ss.str("");
	ss << " - Pressure Plate";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 14;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends11 at the Right
	ss.str("");
	ss << "D";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 15;
	g_Console.writeToBuffer(c, ss.str(), 0xF0);
	ss.str("");
	ss << " - Door";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 15;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends12 at the Right
	ss.str("");
	ss << "C";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 16;
	g_Console.writeToBuffer(c, ss.str(), 0xB0);
	ss.str("");
	ss << " - Checkpoint";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 16;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends13 at the Right
	ss.str("");
	ss << "Y";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 17;
	g_Console.writeToBuffer(c, ss.str(), 0x02);
	ss.str("");
	ss << " - Charge Trap";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 17;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends14 at the Right
	ss.str("");
	ss << "U";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 18;
	g_Console.writeToBuffer(c, ss.str(), 0x0D);
	ss.str("");
	ss << " - Stalker";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 18;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends15 at the Right
	ss.str("");
	ss << "Q";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 19;
	g_Console.writeToBuffer(c, ss.str(), 0x02);
	ss.str("");
	ss << " - Double Pivot";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 19;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends16 at the Right
	ss.str("");
	ss << "R";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 20;
	g_Console.writeToBuffer(c, ss.str(), 0x50);
	ss.str("");
	ss << " - Random Trap";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 20;
	g_Console.writeToBuffer(c, ss.str());

	//Displays instructions1 at the Bottom
	ss.str("");
	ss << "WASD and arrowkeys - Move";
	c.X = 50;
	c.Y = g_Console.getConsoleSize().Y - 2;
	g_Console.writeToBuffer(c, ss.str());
	//Displays instructions2 at the Bottom
	ss.str("");
	ss << "R - Reset(lose a life)";
	c.X = 50;
	c.Y = g_Console.getConsoleSize().Y - 1;
	g_Console.writeToBuffer(c, ss.str());
	//Displays instructions3 at the Bottom
	ss.str("");
	ss << "ESC - Quit game";
	c.X = 80;
	c.Y = g_Console.getConsoleSize().Y - 2;
	g_Console.writeToBuffer(c, ss.str());
	//Displays instructions4 at the Bottom
	ss.str("");
	ss << "H - Exit to Home Screen";
	c.X = 80;
	c.Y = g_Console.getConsoleSize().Y - 1;
	g_Console.writeToBuffer(c, ss.str());

	std::ostringstream cd, ra;
	cd << "(" << playerInfo.m_cLocation.X << ", " << playerInfo.m_cLocation.Y << ")"; //coord
	c.X = g_Console.getConsoleSize().X - 80;
	c.Y = 25;
	g_Console.writeToBuffer(c, cd.str(), 0x0f);

	//std::ostringstream fk; // testing wholly phuck
	//fk << "ChangesArrayOne[1] = (" << ChangesArrayOne[1] << ")"; //coord
	//c.X = g_Console.getConsoleSize().X - 33;
	//c.Y = 24;
	//g_Console.writeToBuffer(c, fk.str(), 0x0f);

	//ra << "Respawn at: (" << NewX << ", " << NewY << ")"; //coord
	//c.X = g_Console.getConsoleSize().X - 25;
	//c.Y = 29;
	//g_Console.writeToBuffer(c, ra.str(), 0x0f);

} // added coord display (for testing purposes)

void renderLives(struct SGameChar &playerInfo, string &NumberOfLives, enum EGAMESTATES &g_eGameState){

	if (playerInfo.m_iLife == 3)
	{
		NumberOfLives = (char)3;
		NumberOfLives += (char)3;
		NumberOfLives += (char)3;
	}
	else if (playerInfo.m_iLife == 2)
	{
		NumberOfLives = (char)3;
		NumberOfLives += (char)3;
	}
	else if (playerInfo.m_iLife == 1)
	{
		NumberOfLives = (char)3;
	}
	else
	{
		g_eGameState = S_DEFEAT;
	}
}

#include "user_interface.h"

void renderUI2(Console &g_Console, string NumberOfLives, struct SGameChar &playerInfo) //For level 2
{
	COORD c;
	std::ostringstream ss;
	//Displays the Level at the Right
	ss.str("");
	ss << "Stage: " << "<<" << "2" << ">>"; //Change to Level with buttons
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0xC);

	//Displays Lives at the Right
	ss.str("");
	ss << "Lives: " << NumberOfLives; //Change to Number of Lives
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 1;
	g_Console.writeToBuffer(c, ss.str(), 0xC);

	//Displays Difficulty at the Right
	ss.str("");
	ss << "Difficulty: " << "Hell"; //Change to Difficulty
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 2;
	g_Console.writeToBuffer(c, ss.str(), 0xC);

	//Displays Legend at the Right
	ss.str("");
	ss << "Legend:"; //Add boxes
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 4;
	g_Console.writeToBuffer(c, ss.str(), 0xE0);

	//Displays Legends1 at the Right
	ss.str("");
	ss << "#";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 5;
	g_Console.writeToBuffer(c, ss.str(), 0x88);
	ss.str(" - Walls");
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 5;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends2 at the Right
	ss.str("");
	ss << (char)2 << " - Character";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 6;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends3 at the Right
	ss.str("");
	ss << "F";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 7;
	g_Console.writeToBuffer(c, ss.str(), 0xE0);
	ss.str("");
	ss << " - Fan";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 7;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends4 at the Right
	ss.str("");
	ss << "W";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 8;
	g_Console.writeToBuffer(c, ss.str(), 0x35);
	ss.str("");
	ss << " - Fan Switch";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 8;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends5 at the Right
	ss.str("");
	ss << "S";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 9;
	g_Console.writeToBuffer(c, ss.str(), 0x40);
	ss.str("");
	ss << " - Spike";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 9;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends6 at the Right
	ss.str("");
	ss << "Q";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 10;
	g_Console.writeToBuffer(c, ss.str(), 0x02);
	ss.str("");
	ss << " - Double Pivot";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 10;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends7 at the Right
	ss.str("");
	ss << "9";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 11;
	g_Console.writeToBuffer(c, ss.str(), 0x02);
	ss.str("");
	ss << " - Double Pivot";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 11;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends8 at the Right
	ss.str("");
	ss << "T";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 12;
	g_Console.writeToBuffer(c, ss.str(), 0x30);
	ss.str("");
	ss << " - Falling Trap";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 12;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends9 at the Right
	ss.str("");
	ss << "G";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 13;
	g_Console.writeToBuffer(c, ss.str(), 0xE0);
	ss.str("");
	ss << " - Generator";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 13;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends10 at the Right
	ss.str("");
	ss << "E";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 14;
	g_Console.writeToBuffer(c, ss.str(), 0xC0);
	ss.str("");
	ss << " - Electric Floor";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 14;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends11 at the Right
	ss.str("");
	ss << "P";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 15;
	g_Console.writeToBuffer(c, ss.str(), 0x21);
	ss.str("");
	ss << " - Pressure Plate";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 15;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends12 at the Right
	ss.str("");
	ss << "D";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 16;
	g_Console.writeToBuffer(c, ss.str(), 0xF0);
	ss.str("");
	ss << " - Door";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 16;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends13 at the Right
	ss.str("");
	ss << "C";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 17;
	g_Console.writeToBuffer(c, ss.str(), 0xB0);
	ss.str("");
	ss << " - Checkpoint";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 17;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends14 at the Right
	ss.str("");
	ss << "Y";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 18;
	g_Console.writeToBuffer(c, ss.str(), 0x02);
	ss.str("");
	ss << " - Charge Trap";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 18;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends15 at the Right
	ss.str("");
	ss << "U";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 19;
	g_Console.writeToBuffer(c, ss.str(), 0x0D);
	ss.str("");
	ss << " - Stalker";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 19;
	g_Console.writeToBuffer(c, ss.str());
	//Displays Legends16 at the Right
	ss.str("");
	ss << "R";
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 20;
	g_Console.writeToBuffer(c, ss.str(), 0x50);
	ss.str("");
	ss << " - Random Trap";
	c.X = g_Console.getConsoleSize().X + 101;
	c.Y = 20;
	g_Console.writeToBuffer(c, ss.str());

	//Displays instructions1 at the Bottom
	ss.str("");
	ss << "WASD and arrowkeys - Move";
	c.X = 50;
	c.Y = g_Console.getConsoleSize().Y - 2;
	g_Console.writeToBuffer(c, ss.str());
	//Displays instructions2 at the Bottom
	ss.str("");
	ss << "R - Reset(lose a life)";
	c.X = 50;
	c.Y = g_Console.getConsoleSize().Y - 1;
	g_Console.writeToBuffer(c, ss.str());
	//Displays instructions3 at the Bottom
	ss.str("");
	ss << "ESC - Quit game";
	c.X = 80;
	c.Y = g_Console.getConsoleSize().Y - 2;
	g_Console.writeToBuffer(c, ss.str());
	//Displays instructions4 at the Bottom
	ss.str("");
	ss << "H - Exit to Home Screen";
	c.X = 80;
	c.Y = g_Console.getConsoleSize().Y - 1;
	g_Console.writeToBuffer(c, ss.str());

	std::ostringstream cd, ra;
	cd << "(" << playerInfo.m_cLocation.X << ", " << playerInfo.m_cLocation.Y << ")"; //coord
	c.X = g_Console.getConsoleSize().X - 80;
	c.Y = 25;
	g_Console.writeToBuffer(c, cd.str(), 0x0f);

	//std::ostringstream fk; // testing wholly phuck
	//fk << "ChangesArrayOne[1] = (" << ChangesArrayOne[1] << ")"; //coord
	//c.X = g_Console.getConsoleSize().X - 33;
	//c.Y = 24;
	//g_Console.writeToBuffer(c, fk.str(), 0x0f);

	//ra << "Respawn at: (" << NewX << ", " << NewY << ")"; //coord
	//c.X = g_Console.getConsoleSize().X - 25;
	//c.Y = 29;
	//g_Console.writeToBuffer(c, ra.str(), 0x0f);

} // added coord display (for testing purposes)