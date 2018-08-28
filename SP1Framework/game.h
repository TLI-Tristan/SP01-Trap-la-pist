#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "collision.h"
#include "GameAsset.h"
#include "user_interface.h"
#include "levels.h"

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_ESCAPE,
	K_SPACE,
	K_RESET,
	K_HOME,
	K_RESUME,
	K_ENTER,
	K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_GAMEMENU,
    S_GAME,
	S_DEFEAT,
	S_VICTORY,
    S_COUNT
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
	int m_iLife;
	int m_iRespawnX;
	int m_iRespawnY;
};

struct SGameMovingTrap
{
	COORD m_cLocation;
	bool  m_bActive;
	int m_cDirection;
};

struct SGameTrap
{
	COORD m_cLocation;
	bool  m_bActive;
};

struct storage2 
{
	COORD m_cOne;
	COORD m_cTwo;
	COORD m_cThree;
	COORD m_cFour;
	int num;
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void changeMapStorageLevel1();
void changeMapStorageLevel2();
void gameMenu();			// waits for player to choose what they want to do
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderGameMenu();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void renderDefeatScreen();  // Changes to defeat screen when die
void renderVictoryScreen(); // Changes to victory screen when win

#endif // _GAME_H