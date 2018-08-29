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
#include <Windows.h>
#pragma comment (lib,"Winmm.lib")

using namespace std;

double g_dElapsedTime;
double g_dDeltaTime;
double g_dTrapTime;
double g_fTrapTime;
double g_dTrapTime2;
double g_dTrapTime3;
double g_dBouncingTrap;
double g_dRandomeMovementTrapTime;

double g_sTrapTime;
double g_leftFanTrapTime, g_rightFanTrapTime, g_upFanTrapTime, g_downFanTrapTime;


bool g_abKeyPressed[K_COUNT];
int Choice;
char mapStorage[100][100];
string NumberOfLives;
int LevelSelected = 0;

bool bGotTrapPos;
bool bGotTrapPos2;

// Game specific variables here
SGameChar   g_sChar;
SGameMovingTrap g_sMovingTrap[8];
SGameTrap g_fTrap[34];
SGameTrap g_sDoublePivotTrap;
SGameTrap g_sBouncingTrap;
SGameTrap g_sChargeTrap[12];
SGameTrap g_sRandomMovementTrap[28];
SGameTrap g_sStalkerTrap[7];
SGameTrap g_leftFanTrap[5], g_rightFanTrap[5], g_upFanTrap[5], g_downFanTrap[5];
storage lineArray[100];

int ChangesArrayOne[50];
int ChangesArrayTwo[50];

EGAMESTATES g_eGameState = S_GAMEMENU;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(180, 35, "SP1 Framework");

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
	g_fTrapTime = 0.0;
	g_dTrapTime2 = 0.0;
	g_dBouncingTrap = 0.0;
	g_sTrapTime = 0.0;
	g_dRandomeMovementTrapTime = 0.0;

	g_leftFanTrapTime = 0.0, g_rightFanTrapTime = 0.0, g_upFanTrapTime = 0.0, g_downFanTrapTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_GAMEMENU;		

    g_sChar.m_cLocation.X = 1;
    g_sChar.m_cLocation.Y = 28;
    g_sChar.m_bActive = true;
	g_sChar.m_iLife = 3;
	g_sChar.m_iRespawnX = 1;
	g_sChar.m_iRespawnY = 28;

	g_sBouncingTrap.m_cLocation.X = 40;
	g_sBouncingTrap.m_cLocation.Y = 8;

    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");
	Choice = 1;

	bGotTrapPos = false;
	bGotTrapPos2 = false;
	initMovingTrap(g_sMovingTrap);
	initFallingTrap(g_fTrap);
	ChangesArrayOne[50] = { 0, };
	ChangesArrayTwo[50] = { 0, };
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
	g_abKeyPressed[K_RESUME] = isKeyPressed(0x4F);
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
	g_fTrapTime += dt;
	g_dTrapTime2 += dt;
	g_dTrapTime3 += dt;
	g_dBouncingTrap += dt;
	g_sTrapTime += dt;
	g_dRandomeMovementTrapTime += dt;

	g_leftFanTrapTime += dt, g_rightFanTrapTime += dt, g_downFanTrapTime += dt, g_upFanTrapTime += dt;

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
		case 1:  // set LevelSelected values (for hard-coding level assets)
			changeMapStorageLevel1();
			g_eGameState = S_GAME;
			break;
		case 2:
			changeMapStorageLevel2();
			g_eGameState = S_GAME;
			break;
		case 3: g_bQuitGame = true;
			break;
		}
	}
}

void changeMapStorageLevel1() {

	if (LevelSelected != 1) {

		string line;
		ifstream myfile("maze.txt");
		int i = 0;
		int pos = 0;
		if (myfile.is_open())
		{
			PlaySound(TEXT("Silent.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
		LevelSelected = 1;
	}

	resetGame(g_sChar, ChangesArrayOne, g_fTrap, bGotTrapPos);
}

void changeMapStorageLevel2() {

	if (LevelSelected != 2) {

		string line;
		ifstream myfile("HellMode.txt");
		int i = 0;
		int pos = 0;
		if (myfile.is_open())
		{
			PlaySound(TEXT("Silent.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
		LevelSelected = 2;
	}
	resetGame2(g_sChar, ChangesArrayTwo, bGotTrapPos2);

}

void gameplay()            // gameplay logic
{
	
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
	if (LevelSelected == 1) {
		movingTrap(g_dTrapTime, g_sMovingTrap);
		fallingTrap(g_fTrapTime, g_fTrap);
		FanFunctionMain(g_sChar, mapStorage, g_Console, g_leftFanTrap, g_rightFanTrap, g_upFanTrap, g_downFanTrap);
		leftFanMovement(g_leftFanTrapTime, g_sChar, mapStorage, g_leftFanTrap);
		rightFanMovement(g_rightFanTrapTime, g_sChar, mapStorage, g_rightFanTrap);
		upFanMovement(g_upFanTrapTime, g_sChar, mapStorage, g_upFanTrap);
		downFanMovement(g_downFanTrapTime, g_sChar, mapStorage, g_downFanTrap);
	}
	else if (LevelSelected == 2) {
		doublePivotTrap(g_dTrapTime, g_sDoublePivotTrap, g_dTrapTime2);
		bouncingTrap(g_dBouncingTrap, g_sBouncingTrap, lineArray);
		StalkerFunctionMain(g_sChar, mapStorage, g_sStalkerTrap);
		StalkerFunctionMovement(g_sTrapTime, g_sChar, mapStorage, g_sStalkerTrap);
		chargeTrap(g_dTrapTime3, g_sChargeTrap);
		randomMovementTrap(g_dRandomeMovementTrapTime, g_sRandomMovementTrap);
	}

	collisionChecker(LevelSelected, g_sChar, mapStorage, g_sMovingTrap, g_fTrap, g_sDoublePivotTrap, g_sBouncingTrap, g_sStalkerTrap, g_sChargeTrap, g_sRandomMovementTrap, lineArray);
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
		if (mapStorage[(int)g_sChar.m_cLocation.Y - 1][(int)g_sChar.m_cLocation.X + 1] != '#')
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
	if (g_abKeyPressed[K_RESET])
	{
		playerKilled(g_sChar);
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_HOME])
	{
		//resetGame();
		gameMenu();
		PlaySound(TEXT("Silent.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}

	if (LevelSelected == 1) {
		//FanFunctionMain(g_sChar, mapStorage, g_Console); // calls main fan function
		if (bSomethingHappened)
		{
			// set the bounce time to some time in the future to prevent accidental triggers
			g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough

			ArrayLevelOneDetect(g_sChar, ChangesArrayOne); // Detect pressure plates etc presses
		}
	}
	else if (LevelSelected == 2) {
		/*FanFunctionMain(g_sChar, mapStorage, g_Console);*/
		if (bSomethingHappened)
		{
			// set the bounce time to some time in the future to prevent accidental triggers
			
			g_dBounceTime = g_dElapsedTime + 0.1;

			g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough

			ArrayLevelTwoDetect(g_sChar, ChangesArrayTwo); // Detect pressure plates etc presses
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
		PlaySound(TEXT("MainMenu.wav"), NULL, SND_FILENAME | SND_NOSTOP | SND_ASYNC);
		while (getline(myfile, line))
		{
			d.Y = i;
			p = 0;
			for (j = 0; j < 120; j++)
			{
				NameStorage[i][j] = line[j]; // Y,X
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
	c.X = c.X / 2 - 49;
	g_Console.writeToBuffer(c, "Normal Stage (more like ez)", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 49;
	g_Console.writeToBuffer(c, "HELL Stage (HEHEHEHAHAHOHO)", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 49;
	g_Console.writeToBuffer(c, "Exit Game (noooo pls :<)", 0x03);
	c.Y = 16 + Choice; //Arrow location
	c.X = g_Console.getConsoleSize().X / 2 - 52;
	g_Console.writeToBuffer(c, "->", 0x03);
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
		PlaySound(TEXT("Defeat.wav"), NULL, SND_FILENAME | SND_NOSTOP | SND_ASYNC);
		while (getline(myfile, line))
		{
			d.Y = i;
			p = 0;
			for (j = 0; j < 120; j++)
			{
				NameStorage[i][j] = line[j]; // Y,X
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
			PlaySound(TEXT("Silent.wav"), NULL, SND_FILENAME | SND_NOSTOP | SND_ASYNC);
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
				NameStorage[i][j] = line[j]; // Y,X
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
			PlaySound(TEXT("Silent.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		myfile.close();
	}
}

void renderGame()
{
	renderCollisionCheck(g_Console);
	renderMap();        // renders the map to the buffer first
	renderCharacter(g_Console, g_sChar);  // renders the character into the buffer
	renderLives(g_sChar, NumberOfLives, g_eGameState);
	PlaySound(TEXT("Game.wav"), NULL, SND_FILENAME | SND_NOSTOP | SND_ASYNC);

    if (LevelSelected == 1) {
		renderMovingTrap(g_Console, g_sMovingTrap);
		renderFallingTrap(g_Console, g_fTrap);
		renderUI(g_Console, NumberOfLives, g_sChar);
	}
	else if (LevelSelected == 2) {
		renderDoublePiovtTrap(g_Console, g_sDoublePivotTrap);
		renderUI2(g_Console, NumberOfLives, g_sChar);
		renderBouncingTrap(g_Console, g_sBouncingTrap, lineArray);
		renderStalkerTrap(g_Console, g_sStalkerTrap);
		renderChargeTrap(g_Console, g_sChargeTrap);
		renderRandomMvementTrap(g_Console, g_sRandomMovementTrap);
	}
}

void renderMap()
{

	COORD c;
	int pos = 0;
	string line;
	int i = 0;
	

	if (LevelSelected == 1) // FOR LEVEL ONE
	{

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
				else if (mapStorage[k][j] == 'l')
				{
					mapStorage[k][j] = 'N';
				}
			}
		}

		ArrayLevelOneActivate(g_sChar, ChangesArrayOne, mapStorage, g_fTrap, g_eGameState); // Activate traps
	}

	if (LevelSelected == 2)
	{
		for (int k = 0; k < 30; k++) // Reset Traps loop
		{
			for (int j = 0; j < 80; j++)
			{
				if (mapStorage[k][j] == ',')
				{
					mapStorage[k][j] = 'D';
				}
			}
		}

		ArrayLevelTwoActivate(g_sChar, ChangesArrayTwo, mapStorage, g_eGameState); // Activate traps
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

	if (bGotTrapPos == false && LevelSelected == 1)
	{
		getMovingTrapPos(mapStorage, g_sMovingTrap);
		getFallingTrapPos(mapStorage, g_fTrap);
		getFanTrapPos(mapStorage, g_leftFanTrap, g_rightFanTrap, g_upFanTrap, g_downFanTrap);
		bGotTrapPos = true;
	}
	else if (bGotTrapPos2 == false && LevelSelected == 2) {

		getDoublePiovtTrapPos(mapStorage, g_sDoublePivotTrap);
		getStalkerTrapPos(mapStorage, g_sStalkerTrap);
		getChargeTrapPos(mapStorage, g_sChargeTrap);
		getRandomMovementTrapPos(mapStorage, g_sRandomMovementTrap);
		bGotTrapPos2 = true;
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