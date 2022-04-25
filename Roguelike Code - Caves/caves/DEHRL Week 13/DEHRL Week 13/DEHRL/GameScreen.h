#pragma once
#include "Screen.h"
#include "Dungeon.h"
// screen that manages the game play.  This has a pointer to a dungeon that needs to be removed.
class GameScreen :
	public Screen
{
public:
	GameScreen();
	virtual ~GameScreen();

	// Inherited via Screen
	// return the games creen id
	virtual ScreenID getID();
	// initialize the dungeon
	virtual void initialize();
};