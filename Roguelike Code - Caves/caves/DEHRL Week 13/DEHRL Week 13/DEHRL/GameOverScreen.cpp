#include "stdafx.h"
#include "GameOverScreen.h"
#include "Text.h"
#include "DEHGE.h"
#include "Constants.h"
// game over screen works much like the splash screen, but does not
// go away with a key press - this is because testing showed that
// the user was likely pounding on the attack keys, and would
// immediately clsoe the game over screen without even seeing it.
GameOverScreen::GameOverScreen()
{
	timeShown = 0;

}

GameOverScreen::~GameOverScreen()
{
}

// which screen is this
ScreenID GameOverScreen::getID()
{
	return ScreenID::GAME_OVER_SCREEN;
}

//add the text, and then connect us to the game engine
void GameOverScreen::initialize()
{
	// add the title
	Text *t = new Text();
	t->setText("You have died.");
	t->setPosition(32, 10);
	t->useOffset(false);
	// and start getting events from the game engine
	DEHGE::getInstance()->addView(getID(), t);
	DEHGE::getInstance()->addModel(getID(), this);
	DEHGE::getInstance()->addMouseController(getID(), this);
}

// time has passed
void GameOverScreen::update(int milliseconds)
{
	timeShown += milliseconds; // accumulate it
	if (timeShown > GAME_OVER_TIME)
	{
		// after 5 seconds, exit
		DEHGE::getInstance()->requestShutDown();
	}
}

// if the mouse is clicked, show the menu screen.
void GameOverScreen::leftMouseDown(int x, int y)
{
	DEHGE::getInstance()->requestShutDown();
}