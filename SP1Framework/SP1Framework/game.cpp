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

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_GAMEMENU;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

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
    g_eGameState = S_GAMEMENU;		//18   13		8

    g_sChar.m_cLocation.X = 0;
    g_sChar.m_cLocation.Y = 28;
    g_sChar.m_bActive = true;

	initGameAsset();

    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");
	Choice = 1;
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
			
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void gameMenu()    // waits for user choice
{
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
		case 1: g_eGameState = S_GAME;
			break;
		case 3: g_bQuitGame = true;
			break;
		}
	}

}
//moveTrap Global variable

int direction = 1;



void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
	movingTrap(direction,g_dTrapTime);
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
		g_sChar.m_cLocation.Y--;
		bSomethingHappened = true;
	}
}
if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0 && g_sChar.m_cLocation.X < 79) // FOR "LEFT"
{
	//Beep(1440, 30);
	if (mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X - 1] != '#')
	{
		g_sChar.m_cLocation.X--;
		bSomethingHappened = true;
	}

}
if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 7) // FOR "DOWN"
{
	//Beep(1440, 30);
	if (mapStorage[(int)g_sChar.m_cLocation.Y][(int)g_sChar.m_cLocation.X] != '#')
	{
		g_sChar.m_cLocation.Y++;
		bSomethingHappened = true;
	}

}
if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 41) // FOR "RIGHT"
{
	//Beep(1440, 30);
	if (mapStorage[(int)g_sChar.m_cLocation.Y-1][(int)g_sChar.m_cLocation.X+1] != '#')
	{
		g_sChar.m_cLocation.X++;
		bSomethingHappened = true;
	}

}
if (g_abKeyPressed[K_SPACE])
{
	g_sChar.m_bActive = !g_sChar.m_bActive;
	bSomethingHappened = true;
}

if (bSomethingHappened)
{
	// set the bounce time to some time in the future to prevent accidental triggers
	g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
}
}
void processUserInput()
{
	// quits the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE])
		g_bQuitGame = true;
}

void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x00);
}

void renderGameMenu()  // renders the game menu	//TODO: change this to game menu
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 9;
	g_Console.writeToBuffer(c, "Normal Mode (more like ez)", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "HELL MODE (HEHEHEHAHAHOHO)", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "Exit Game (noooo pls :<)", 0x03);

	c.Y = c.Y / 3 + 7; // ARROW LOCATION

	c.X = g_Console.getConsoleSize().X / 2 - 12;

	switch (Choice) {
	case 1: g_Console.writeToBuffer(c, "->", 0x03);
		break;
	case 2: c.Y += 1;

		g_Console.writeToBuffer(c, "->", 0x03);
		break;
	case 3: c.Y += 2;
		g_Console.writeToBuffer(c, "->", 0x03);
		break;
	}


}

void renderGame()
{
	renderMap();        // renders the map to the buffer first
	renderCharacter();  // renders the character into the buffer
	renderMovingTrap(g_Console);
	renderUI();
	collisionChecker(g_sChar);
}

void renderMap()
{

	COORD c;
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
			else if (mapStorage[k][j] == 'F')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0xE0);
			}
			else if (mapStorage[k][j] == 'T')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x30);
			}
			else if (mapStorage[k][j] == 'A')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x90);
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
			else
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x00);
			}
			pos2++;
		}
		pos++;
	}



}


void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
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

void renderUI()
{
	COORD c;
	std::ostringstream ss;
	//Displays the Level at the Right
	ss.str("");
	ss << "Level: " << "<<" << "sth" << ">>"; //Change to Level with buttons
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0xC);

	//Displays Lives at the Right
	ss.str("");
	ss << "Lives: " << (char)3 << (char)3 << (char)3; //Change to Number of Lives
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
	g_Console.writeToBuffer(c, ss.str(), 0x11);
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
	g_Console.writeToBuffer(c, ss.str(), 0x90);
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
	//Displays Reset and Home Button at the Right
	ss.str("");
	ss << "Reset"; //Program in the buttons
	c.X = g_Console.getConsoleSize().X + 100;
	c.Y = 18;
	g_Console.writeToBuffer(c, ss.str(), 0xE0);

	ss.str("");
	ss << "Home"; //Program in the buttons
	c.X = g_Console.getConsoleSize().X + 115;
	c.Y = 18;
	g_Console.writeToBuffer(c, ss.str(), 0xE0);

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
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}
