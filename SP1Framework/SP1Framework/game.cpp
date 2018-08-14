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
bool    g_abKeyPressed[K_COUNT];
int Choice;
char mapStorage[100][100];

// Game specific variables here
SGameChar   g_sChar;
SGameTrap	g_sTrap01;
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

    // sets the initial state for the game
    g_eGameState = S_GAMEMENU;		//18   13		8

    g_sChar.m_cLocation.X = 0;
    g_sChar.m_cLocation.Y = 28;
    g_sChar.m_bActive = true;

	g_sTrap01.m_bActive = true;
	g_sTrap01.m_cLocation.X = 8;
	g_sTrap01.m_cLocation.Y = 18;

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

void movingTrap() {

	bool bChangeDirection = false;

	if (g_dDeltaTime >= 0.01) {
		if (bChangeDirection == false) {
			g_sTrap01.m_cLocation.Y -= 1;
		}
		else {
			g_sTrap01.m_cLocation.Y += 1;
		}
	}
	if (g_sTrap01.m_cLocation.Y == 13) {
		bChangeDirection = true;
	}

}
void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
	movingTrap();
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

<<<<<<< HEAD
	c.Y = c.Y / 3 + 7;
=======
	c.Y = c.Y / 3 + 7; // ARROW LOCATION
>>>>>>> 12a890eed1859eaab44773ba5e5e0ef1ee97a064
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
	renderMovingTrap();
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
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x0);
			}
			else if (mapStorage[k][j] == 'S') 
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x25A1);
			}
			else if (mapStorage[k][j] == 'D')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0xC);
			}
			else if (mapStorage[k][j] == 'E')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x25);
			}
			else if (mapStorage[k][j] == 'P')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x27);
			}
			else if (mapStorage[k][j] == 'F')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x29);
			}
			else if (mapStorage[k][j] == 'T')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x10);
			}
			else if (mapStorage[k][j] == 'A')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x99);
			}
			else if (mapStorage[k][j] == 'W')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x35);
			}
			else if (mapStorage[k][j] == 'C')
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0x18);
			}
			else 
			{
				g_Console.writeToBuffer(c, mapStorage[k][j], 0xFF);
			}
			pos2++;
		}
		pos++;
	}


}

void renderMovingTrap() {
	WORD trapColor = 0x0C;
	{
		trapColor = 0x0A;
	}
	g_Console.writeToBuffer(g_sTrap01.m_cLocation, (char)1, trapColor);

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
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}
