// This is the main file for the game logic and function
// gud day 14/8/2018
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

double  g_dElapsedTime;
double  g_dDeltaTime;
double g_dTrapTime;

bool    g_abKeyPressed[K_COUNT];
int Choice;
char mapStorage[100][100];
string NumberOfLives;
int LevelSelected = 0;
int ChangesArrayOne[50] = { 0, };
bool bGotTrapPos;

// Game specific variables here
SGameChar   g_sChar;
SGameTrap g_sMovingTrap[8];

EGAMESTATES g_eGameState = S_GAMEMENU;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
int FanBlowLeftDelay = 0, FanBlowRightDelay = 0, FanBlowUpDelay = 0, FanBlowDownDelay = 0;
int AllowedMaxFanDelay = 3; // maximum frames allowed for delay CAN BE EDITED

struct SGameTrap *ptr;

// Console object
Console g_Console(120, 35, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;
	g_dTrapTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_GAMEMENU;		

    g_sChar.m_cLocation.X = 13;
    g_sChar.m_cLocation.Y = 13;
    g_sChar.m_bActive = true;
	g_sChar.m_iLife = 3;
	g_sChar.m_iRespawnX = 1;
	g_sChar.m_iRespawnY = 28;

    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");
	Choice = 1;

	bGotTrapPos = false;

	string line;
	ifstream myfile("maze.txt");
	int i = 0;
	int pos = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (int j = 0; j < 80; j++)
			{
				mapStorage[i][j] = line[j]; // WHY IS IT Y,X
			}
			i++;
		}
		myfile.close();
	}
}


//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP)    || isKeyPressed(0x57); // "WASD" added
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN)  || isKeyPressed(0x53);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT)  || isKeyPressed(0x41);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT) || isKeyPressed(0x44);
    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_ENTER]  = isKeyPressed(VK_RETURN);
	g_abKeyPressed[K_RESET] = isKeyPressed(0x52);
	g_abKeyPressed[K_HOME] = isKeyPressed(0x48);
	g_abKeyPressed[K_PAUSE] = isKeyPressed(0x50);
}
//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;
	g_dTrapTime += dt;

    switch (g_eGameState)
    {
        case S_GAMEMENU : gameMenu(); // game logic for the splash screen
            break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
    }
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        case S_GAMEMENU: renderGameMenu();
            break;
        case S_GAME: renderGame();
            break;
		case S_DEFEAT: renderDefeatScreen();
			break;
		case S_PAUSE: renderPauseScreen();
			break;
		case S_VICTORY: renderVictoryScreen();
			break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void gameMenu()
{
	g_eGameState = S_GAMEMENU;
	bool bSelection = false;

	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (g_abKeyPressed[K_DOWN] && Choice != 3)
	{
		Choice += 1;
		bSelection = true;
	}
	if (g_abKeyPressed[K_UP] && Choice != 1)
	{
		Choice -= 1;
		bSelection = true;
	}

	if (bSelection)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
	if (g_abKeyPressed[K_ENTER]) { // Press enter to start game
		switch (Choice) {
		case 1: LevelSelected = 1; // set LevelSelected values (for hard-coding level assets)
			g_eGameState = S_GAME;

			g_sChar.m_iLife = 3;			// reset lives
			g_sChar.m_cLocation.X = 1;		// reset coord x
			g_sChar.m_cLocation.Y = 28;		// reset coord y
			newRespawnLocation(g_sChar);	// reset spawn

			for (int i = 0; i < 50; i++)	// reset array
			{
				ChangesArrayOne[i] = 0;
			}
			g_sChar.m_iLife = 3;
			g_sChar.m_cLocation.X = 1;
			g_sChar.m_cLocation.Y = 28;
			ChangesArrayOne[14] = 0;
			break;
		case 3: g_bQuitGame = true;
			break;
		}
	}
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
	movingTrap(g_dTrapTime, g_sMovingTrap);
	collisionChecker(g_sChar, mapStorage, g_sMovingTrap);
	// sound can be played here too.
	
}

void moveCharacter()
{
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 2) // FOR "UP"
{
	//Beep(1440, 30);
	if (mapStorage[(int)g_sChar.m_cLocation.Y - 2][(int)g_sChar.m_cLocation.X] != '#')
	{
		if (mapStorage[(int)g_sChar.m_cLocation.Y - 2][(int)g_sChar.m_cLocation.X] != 'D')
		{
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}	
	}
}
if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0 && g_sChar.m_cLocation.X < 79) // FOR "LEFT"
{
	//Beep(1440, 30);
	if (mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X - 1] != '#')
	{
		if (mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X - 1] != 'D')
		{
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
	}

}
if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 7) // FOR "DOWN"
{
	//Beep(1440, 30);
	if (mapStorage[(int)g_sChar.m_cLocation.Y][(int)g_sChar.m_cLocation.X] != '#')
	{
		if (mapStorage[(int)g_sChar.m_cLocation.Y][(int)g_sChar.m_cLocation.X] != 'D') 
		{
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
	}

}
if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 41) // FOR "RIGHT"
{
	//Beep(1440, 30);
	if (mapStorage[(int)g_sChar.m_cLocation.Y-1][(int)g_sChar.m_cLocation.X+1] != '#')
	{
		if (mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 1] != 'D')
		{
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}
	}

}
if (g_abKeyPressed[K_SPACE])
{
	g_sChar.m_bActive = !g_sChar.m_bActive;
	bSomethingHappened = true;
}

if (g_abKeyPressed[K_PAUSE])
{
		g_eGameState = S_PAUSE;
}

if (g_abKeyPressed[K_RESET])
{
	g_sChar.m_iLife -= 1;
	respawnAt(g_sChar);
	bSomethingHappened = true;
}

if (g_abKeyPressed[K_HOME])
{
	gameMenu();
	g_sChar.m_iLife = 3;
	
}

if (/*mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 29] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 28] == 'N' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 27] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 26] == 'N' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 25] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 24] == 'N' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 23] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 22] == 'N' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 21] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 20] == 'N' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 19] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 18] == 'N' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 17] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 16] == 'N' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 15] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 14] == 'N' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 13] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 12] == 'N' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 11] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 10] == 'N' ||*/
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 9] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 8] == 'N' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 7] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 6] == 'N' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 5] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 4] == 'N' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 3] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 2] == 'N' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 1] == 'N' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X] == 'N')
{
	if (FanBlowLeftDelay < AllowedMaxFanDelay) // left fan
	{
		FanBlowLeftDelay++;
	}
	else if (FanBlowLeftDelay == AllowedMaxFanDelay && mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X - 1] != '#' && mapStorage[(int)g_sChar.m_cLocation.Y - 2][(int)g_sChar.m_cLocation.X] != 'D')
	{
		if (g_sChar.m_cLocation.X > 0 && g_sChar.m_cLocation.X < 79)
		{
			g_sChar.m_cLocation.X--;
		}
		FanBlowLeftDelay = 0;
	}

}

if (mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X - 9] == 'M' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X - 8] == 'M' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X - 7] == 'M' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X - 6] == 'M' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X - 5] == 'M' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X - 4] == 'M' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X - 3] == 'M' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X - 2] == 'M' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X - 1] == 'M' || mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X] == 'M')
{
	if (FanBlowRightDelay < AllowedMaxFanDelay) // right fan
	{
		FanBlowRightDelay++;
	}
	else if (FanBlowRightDelay == AllowedMaxFanDelay)
	{
		if (g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 41 && mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 1] != '#' && mapStorage[(int)g_sChar.m_cLocation.Y - 2][(int)g_sChar.m_cLocation.X] != 'D')
		{
			g_sChar.m_cLocation.X++;
		}
		FanBlowRightDelay = 0;
	}

}

if (mapStorage[(int)g_sChar.m_cLocation.Y + 9][(int)g_sChar.m_cLocation.X] == 'Z' || mapStorage[(int)g_sChar.m_cLocation.Y + 8][(int)g_sChar.m_cLocation.X] == 'Z' ||
	mapStorage[(int)g_sChar.m_cLocation.Y + 7][(int)g_sChar.m_cLocation.X] == 'Z' || mapStorage[(int)g_sChar.m_cLocation.Y + 6][(int)g_sChar.m_cLocation.X] == 'Z' ||
	mapStorage[(int)g_sChar.m_cLocation.Y + 5][(int)g_sChar.m_cLocation.X] == 'Z' || mapStorage[(int)g_sChar.m_cLocation.Y + 4][(int)g_sChar.m_cLocation.X] == 'Z' ||
	mapStorage[(int)g_sChar.m_cLocation.Y + 3][(int)g_sChar.m_cLocation.X] == 'Z' || mapStorage[(int)g_sChar.m_cLocation.Y + 2][(int)g_sChar.m_cLocation.X] == 'Z' ||
	mapStorage[(int)g_sChar.m_cLocation.Y + 1][(int)g_sChar.m_cLocation.X] == 'Z' || mapStorage[(int)g_sChar.m_cLocation.Y][(int)g_sChar.m_cLocation.X] == 'Z')
{
	if (FanBlowUpDelay < AllowedMaxFanDelay) // up fan // unable to push player if player is IN UP fan
	{
		FanBlowUpDelay++;
	}
	else if (FanBlowUpDelay == AllowedMaxFanDelay)
	{
		if (g_sChar.m_cLocation.Y > 2 && mapStorage[(int)g_sChar.m_cLocation.Y - 2][(int)g_sChar.m_cLocation.X] != '#' && mapStorage[(int)g_sChar.m_cLocation.Y - 2][(int)g_sChar.m_cLocation.X] != 'D')
		{
			g_sChar.m_cLocation.Y--;
		}
		FanBlowUpDelay = 0;
	}

}

if (mapStorage[(int)g_sChar.m_cLocation.Y - 9][(int)g_sChar.m_cLocation.X] == 'X' || mapStorage[(int)g_sChar.m_cLocation.Y - 8][(int)g_sChar.m_cLocation.X] == 'X' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 7][(int)g_sChar.m_cLocation.X] == 'X' || mapStorage[(int)g_sChar.m_cLocation.Y - 6][(int)g_sChar.m_cLocation.X] == 'X' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 5][(int)g_sChar.m_cLocation.X] == 'X' || mapStorage[(int)g_sChar.m_cLocation.Y - 4][(int)g_sChar.m_cLocation.X] == 'X' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 3][(int)g_sChar.m_cLocation.X] == 'X' || mapStorage[(int)g_sChar.m_cLocation.Y - 2][(int)g_sChar.m_cLocation.X] == 'X' ||
	mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X] == 'X' || mapStorage[(int)g_sChar.m_cLocation.Y][(int)g_sChar.m_cLocation.X] == 'X')
{
	if (FanBlowDownDelay < AllowedMaxFanDelay) // down fan
	{
		FanBlowDownDelay++;
	}
	else if (FanBlowDownDelay == AllowedMaxFanDelay)
	{
		if (g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 7 && mapStorage[(int)g_sChar.m_cLocation.Y][(int)g_sChar.m_cLocation.X] != '#' && mapStorage[(int)g_sChar.m_cLocation.Y - 2][(int)g_sChar.m_cLocation.X] != 'D')
		{
			g_sChar.m_cLocation.Y++;
		}
		FanBlowDownDelay = 0;
	}

}



if (bSomethingHappened)
{
	// set the bounce time to some time in the future to prevent accidental triggers
	g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough

	if (LevelSelected == 1) // FOR FIRST LEVEL
	{
		if ((int)g_sChar.m_cLocation.Y - 1 == 18 && (int)g_sChar.m_cLocation.X == 57) // for first falling trap
		{
			ChangesArrayOne[0] = 1;
		}
		if ( ( (int)g_sChar.m_cLocation.Y - 1 == 27 && (int)g_sChar.m_cLocation.X == 28 ) || ( (int)g_sChar.m_cLocation.Y - 1 == 25 && (int)g_sChar.m_cLocation.X == 28) )
		{
			ChangesArrayOne[1] = 1; // for second 2 pressure plates
		}
		if ( (int)g_sChar.m_cLocation.Y - 1 == 23 && (int)g_sChar.m_cLocation.X == 70) // for pressure plate after "2 fake pressure plate"
		{
			ChangesArrayOne[2] = 1;
		}
		if ((int)g_sChar.m_cLocation.Y - 1 == 19 && (int)g_sChar.m_cLocation.X == 64) // for top left at room with 2nd checkpoint
		{
			ChangesArrayOne[3] = 1;
		}
		if ((int)g_sChar.m_cLocation.Y - 1 == 23 && (int)g_sChar.m_cLocation.X == 59) // for bottome left at room with 2nd checkpoint
		{
			ChangesArrayOne[4] = 1;
		}
		if ((int)g_sChar.m_cLocation.Y - 1 == 18 && (int)g_sChar.m_cLocation.X == 78) // for top right at room with 2nd checkpoint
		{
			ChangesArrayOne[5] = 1;
		}
		if ((int)g_sChar.m_cLocation.Y - 1 == 13 && (int)g_sChar.m_cLocation.X == 78) // for rightmost generator
		{
			ChangesArrayOne[6] = 1;
		}
		if ((int)g_sChar.m_cLocation.Y - 1 == 16 && (int)g_sChar.m_cLocation.X == 71) // for pressure plate between spikes
		{
			ChangesArrayOne[7] = 1;
		}
		if ((int)g_sChar.m_cLocation.Y - 1 == 14 && (int)g_sChar.m_cLocation.X == 1) // for leftmost pressure plate
		{
			ChangesArrayOne[8] = 1;
		}
		if ((int)g_sChar.m_cLocation.Y - 1 == 15 && (int)g_sChar.m_cLocation.X == 1) // for leftmost generator
		{
			ChangesArrayOne[9] = 1;
		}
		if ((int)g_sChar.m_cLocation.Y - 1 == 10 && (int)g_sChar.m_cLocation.X == 16 || (int)g_sChar.m_cLocation.Y - 1 == 10 && (int)g_sChar.m_cLocation.X == 17) // for falling trap row room pressure plate
		{
			ChangesArrayOne[10] = 1;
		}
		if ((int)g_sChar.m_cLocation.Y - 1 == 10 && (int)g_sChar.m_cLocation.X == 49) // for spike room generator
		{
			ChangesArrayOne[11] = 1;
		}
		if ((int)g_sChar.m_cLocation.Y - 1 == 10 && (int)g_sChar.m_cLocation.X == 52) // for spike room leftmost pressure plate
		{
			ChangesArrayOne[12] = 1;
		}
		if ((int)g_sChar.m_cLocation.Y - 1 == 27 && (int)g_sChar.m_cLocation.X == 26)
		{
			ChangesArrayOne[13] = 1;
		}
		if ((int)g_sChar.m_cLocation.Y - 1 == 1 && (int)g_sChar.m_cLocation.X == 79)
		{
			ChangesArrayOne[14] = 1;
		}
	}
}
}

void processUserInput() {
	// quits the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE]) {
		g_bQuitGame = true;
	}
}

void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x00);
}

void renderGameMenu()  // renders the game menu	//TODO: change this to game menu
{
	COORD c = g_Console.getConsoleSize();
	COORD d;
	string line;
	ifstream myfile("Name.txt");
	char NameStorage[100][100];
	int i = 0, j = 0;
	int pos = 0;
	int p = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			d.Y = i;
			p = 0;
			for (j = 0; j < 120; j++)
			{
				NameStorage[i][j] = line[j]; // WHY IS IT Y,X
				d.X = p;
				if (NameStorage[i][j] == '#')
				{
					g_Console.writeToBuffer(d, NameStorage[i][j], 0x33);
				}

				else
				{
					g_Console.writeToBuffer(d, NameStorage[i][j], 0x03);
				}
				p++;
			}
			i++;
		}
		myfile.close();
	}
	c.Y = 17;
	c.X = c.X / 2 - 9;
	g_Console.writeToBuffer(c, "Normal Mode (more like ez)", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "HELL MODE (HEHEHEHAHAHOHO)", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "Exit Game (noooo pls :<)", 0x03);
	c.Y = 16 + Choice; //Arrow location
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "->", 0x03);
}

void renderPauseScreen()
{
	COORD c = g_Console.getConsoleSize();
	COORD d;
	string line;
	ifstream myfile("Pause.txt");
	char NameStorage[100][100];
	int i = 0, j = 0;
	int pos = 0;
	int p = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			d.Y = i;
			p = 0;
			for (j = 0; j < 120; j++)
			{
				NameStorage[i][j] = line[j]; // WHY IS IT Y,X
				d.X = p;
				if (NameStorage[i][j] == '#') {
					g_Console.writeToBuffer(d, NameStorage[i][j], 0x44);
				}
				else
				{
					g_Console.writeToBuffer(d, NameStorage[i][j], 0x04);
				}
				p++;
			}
			i++;
		}
		if (g_abKeyPressed[K_HOME])
		{
			gameMenu();
		}
		myfile.close();
	}
	//if (g_abKeyPressed[K_PAUSE])
	//{
	//	gameMenu()
	//}
}

void renderDefeatScreen()
{
	COORD c = g_Console.getConsoleSize();
	COORD d;
	string line;
	ifstream myfile("Defeat.txt");
	char NameStorage[100][100];
	int i = 0, j = 0;
	int pos = 0;
	int p = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			d.Y = i;
			p = 0;
			for (j = 0; j < 120; j++)
			{
				NameStorage[i][j] = line[j]; // WHY IS IT Y,X
				d.X = p;
				if (NameStorage[i][j] == '#') {
					g_Console.writeToBuffer(d, NameStorage[i][j], 0x44);
				}
				else
				{
					g_Console.writeToBuffer(d, NameStorage[i][j], 0x04);
				}
				p++;
			}
			i++;
		}
		if (g_abKeyPressed[K_HOME])
		{
			gameMenu();
		}
		myfile.close();
	}
}

void renderVictoryScreen()
{
	COORD c = g_Console.getConsoleSize();
	COORD d;
	string line;
	ifstream myfile("Victory.txt");
	char NameStorage[100][100];
	int i = 0, j = 0;
	int pos = 0;
	int p = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			d.Y = i;
			p = 0;
			for (j = 0; j < 120; j++)
			{
				NameStorage[i][j] = line[j]; // WHY IS IT Y,X
				d.X = p;
				if (NameStorage[i][j] == '#') {
					g_Console.writeToBuffer(d, NameStorage[i][j], 0xEE);
				}
				else
				{
					g_Console.writeToBuffer(d, NameStorage[i][j], 0x0E);
				}
				p++;
			}
			i++;
		}
		if (g_abKeyPressed[K_HOME])
		{
			gameMenu();
		}
		myfile.close();
	}
}

void renderGame()
{
	renderCollisionCheck(g_Console);
	renderMap();        // renders the map to the buffer first
	renderCharacter(g_Console, g_sChar);  // renders the character into the buffer

	renderMovingTrap(g_Console, g_sMovingTrap);
	renderLives();
	renderUI(g_Console, NumberOfLives, g_sChar);
}

void renderMap()
{

	COORD c;
	int pos = 0;
	string line;

		for (int k = 0; k < 30; k++) // Reset Traps loop
		{
			for (int j = 0; j < 80; j++)
			{
				if (mapStorage[k][j] == ',')
				{
					mapStorage[k][j] = 'D';
				}
				else if (mapStorage[k][j] == '.')
				{
					mapStorage[k][j] = 'E';
				}
				else if (mapStorage[k][j] == 'b')
				{
					mapStorage[k][j] = 'S';
				}
			}
		}

	int i = 0;
	if (LevelSelected == 1) // FOR LEVEL ONE					// LEGEND:
	{															// ',' (Comma) = Deactivated Door
		for (int i = 0; i < 50; i++) // FOR LEVEL ONE			// '.' (FullStop) = Deactivated Electric Floor
		{														// 'b' (b) = Deactivated Spikes
			if (ChangesArrayOne[0] == 1)
			{
				// add first falling traps
				mapStorage[20][54] = ' ', mapStorage[21][57] = ' ', mapStorage[22][54] = ' ', mapStorage[23][57] = ' ';
			}
			if (ChangesArrayOne[1] == 1)
			{
				mapStorage[26][68] = ','; // opens 1st door
			}
			if (ChangesArrayOne[2] == 1)
			{
				mapStorage[22][78] = 'b'; // removes bottom right spike at 2nd checkpoint room
			}
			if (ChangesArrayOne[3] == 1)
			{
				mapStorage[23][64] = 'b';// removes bottom left spike at 2nd checkpoint room
			}
			if (ChangesArrayOne[4] == 1)
			{
				mapStorage[20][71] = 'b'; // removes top right spike at 2nd checkpoint room
			}
			if (ChangesArrayOne[5] == 1)
			{
				mapStorage[17][59] = ','; // opens 2nd door
			}
			if (ChangesArrayOne[6] == 1)
			{
				mapStorage[12][58] = '.', mapStorage[12][59] = '.', mapStorage[12][60] = '.', mapStorage[12][61] = '.', mapStorage[12][62] = '.', mapStorage[12][63] = '.', mapStorage[12][64] = '.', mapStorage[12][65] = '.', mapStorage[12][66] = '.', mapStorage[12][67] = '.', mapStorage[12][68] = '.', mapStorage[12][69] = '.', mapStorage[12][70] = '.', mapStorage[12][71] = '.', mapStorage[12][72] = '.';
				mapStorage[13][58] = '.';
				mapStorage[14][58] = '.', mapStorage[14][60] = '.', mapStorage[14][61] = '.', mapStorage[14][62] = '.', mapStorage[14][63] = '.', mapStorage[14][64] = '.', mapStorage[14][65] = '.', mapStorage[14][66] = '.', mapStorage[14][67] = '.', mapStorage[14][68] = '.', mapStorage[14][69] = '.', mapStorage[14][70] = '.', mapStorage[14][71] = '.', mapStorage[14][72] = '.';
				mapStorage[15][58] = '.', mapStorage[15][60] = '.';
				mapStorage[16][58] = '.', mapStorage[16][60] = '.'; // turns off rightmost electric floors (Coding order follows map display order)
			}
			if (ChangesArrayOne[7] == 1)
			{
				mapStorage[14][43] = ',', mapStorage[15][43] = ','; // opens 3rd door (double door)
			}
			if (ChangesArrayOne[8] == 1)
			{
				mapStorage[11][16] = ',', mapStorage[11][17] = ','; // opens 4th door (double door)
			}
			if (ChangesArrayOne[9] == 1)
			{
				mapStorage[12][2] = '.'; // removes electric floor behind moving traps
				mapStorage[13][2] = '.', mapStorage[13][5] = '.';
										mapStorage[14][5] = '.';
										mapStorage[15][5] = '.';
				mapStorage[16][2] = '.', mapStorage[16][5] = '.';
				mapStorage[17][2] = '.';
			}
			if (ChangesArrayOne[10] == 1)
			{
				mapStorage[5][39] = ',', mapStorage[6][39] = ','; // opens 5th door between electric floors (room with row of falling traps) (double door)
				// add 2nd falling trap
				mapStorage[1][1] = ' ', mapStorage[1][2] = ' ', mapStorage[1][3] = ' ', mapStorage[1][4] = ' ', mapStorage[1][5] = ' ', mapStorage[1][6] = ' ', mapStorage[1][7]= ' ', mapStorage[1][8] = ' ', mapStorage[1][9] = ' ', mapStorage[1][10] = ' ';
				mapStorage[1][11] = ' ', mapStorage[1][12] = ' ', mapStorage[1][13] = ' ', mapStorage[1][14] = ' ', mapStorage[1][15] = ' ', mapStorage[1][16] = ' ', mapStorage[1][17] = ' ', mapStorage[1][18] = ' ', mapStorage[1][19] = ' ', mapStorage[1][20] = ' ';
				mapStorage[1][21] = ' ', mapStorage[1][22] = ' ', mapStorage[1][23] = ' ', mapStorage[1][24] = ' ', mapStorage[1][25] = ' ', mapStorage[1][26] = ' ', mapStorage[1][27] = ' ', mapStorage[1][28] = ' ', mapStorage[1][29] = ' ', mapStorage[1][30] = ' ';
				mapStorage[1][31] = ' ', mapStorage[1][32] = ' ', mapStorage[1][33] = ' ', mapStorage[1][34] = ' ';
			}
			if (ChangesArrayOne[11] == 1)
			{
				mapStorage[9][54] = '.', mapStorage[9][55] = '.', mapStorage[9][56] = '.', mapStorage[9][57] = '.', mapStorage[9][58] = '.', mapStorage[9][59] = '.', mapStorage[9][60] = '.', mapStorage[9][61] = '.', mapStorage[9][62] = '.', mapStorage[9][63] = '.', mapStorage[9][64] = '.', mapStorage[9][65] = '.', mapStorage[9][66] = '.', mapStorage[9][67] = '.';
				mapStorage[4][73] = '.', mapStorage[4][74] = '.', mapStorage[4][75] = '.'; // removes electric floor near row of pressure plates and infront of final door in 2nd last room
			}
			if (ChangesArrayOne[12] == 1)
			{
				mapStorage[3][74] = ',', mapStorage[3][75] = ','; // opens last door (double door)
			}
			if (ChangesArrayOne[13] == 1)
			{
				mapStorage[19][33] = ' ', mapStorage[22][33] = ' ' ; //Fanswitch to disable first few fans
			}
			if (ChangesArrayOne[14] == 1)
			{
				g_eGameState = S_VICTORY;
			}
		}
		

	}

	for (int k = 0; k < 30; k++) {
		int pos2 = 0;
		c.Y = 1 + pos;
		for (int j = 0; j < 80; j++) {
			c.X = pos2;
			if (mapStorage[k][j] == '#') {
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x88);
			}
			else if (mapStorage[k][j] == 'S')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x40);

			}
			else if (mapStorage[k][j] == 'D')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0xF0);
			}
			else if (mapStorage[k][j] == 'E')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0xC0);
			}
			else if (mapStorage[k][j] == 'P')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x21);
			}
			else if (mapStorage[k][j] == '!') // fake pressure plate // act as spikes
			{
				g_Console.writeToBuffer(c, 'P', 0x21);
			}
			else if (mapStorage[k][j] == 'Z' || mapStorage[k][j] == 'X' || mapStorage[k][j] == 'N' || mapStorage[k][j] == 'M') // fans
			{
				g_Console.writeToBuffer(c, 'F', 0xE0);
			}
			else if (mapStorage[k][j] == 'T')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x30);
			}
			else if (mapStorage[k][j] == 'W')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x35);
			}
			else if (mapStorage[k][j] == 'C')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0xB0);
			}
			else if (mapStorage[k][j] == 'G')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0xE0);
			}
			else if (mapStorage[k][j] == '~')
			{
				g_Console.writeToBuffer(c, "WIN" , 0xE0);
			}
			else
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x00);
			}
			pos2++;
		}
		pos++;
	}

		if (bGotTrapPos == false)
		{
			getMovingTrapPos(bGotTrapPos, mapStorage, g_sMovingTrap);
		}
}

void renderLives() {

	if (g_sChar.m_iLife == 3)
	{
		NumberOfLives = (char)3;
		NumberOfLives += (char)3;
		NumberOfLives += (char)3;
	}
	else if (g_sChar.m_iLife == 2)
	{
		NumberOfLives = (char)3;
		NumberOfLives += (char)3;
	}
	else if (g_sChar.m_iLife == 1)
	{
		NumberOfLives = (char)3;
	}
	else
	{
		g_eGameState = S_DEFEAT;
	}
}

void renderFramerate()
{
	COORD c;
	// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << "Frame Rate: " << 1.0 / g_dDeltaTime << "fps";
	c.X = g_Console.getConsoleSize().X; //THIS IS WHERE THE FRAMERATE THINGY AT Initial TOP RIGHT SHOWS UP
	c.Y = g_Console.getConsoleSize().Y - 2;
	g_Console.writeToBuffer(c, ss.str());

	// displays the elapsed time
	ss.str("");
	ss << "Elapsed Time: " << g_dElapsedTime << "secs";
	c.X = 0;
	c.Y = g_Console.getConsoleSize().Y - 2;
	g_Console.writeToBuffer(c, ss.str());
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}