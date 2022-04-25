#include "stdafx.h"
#include "GameScreen.h"
#include "Dungeon.h"

GameScreen::GameScreen()
{
}

GameScreen::~GameScreen()
{
}

// which screen are we
ScreenID GameScreen::getID()
{
	return ScreenID::GAME_SCREEN;
}

// and set the game play screen up to run
void GameScreen::initialize()
{
	// build a dungeon (note that we're no longer keeping it around - it is it's own keeper
	Dungeon *dungeon = Dungeon::getInstance();
	// and get it to dig some maps.
	dungeon->initializeDungeon();
}