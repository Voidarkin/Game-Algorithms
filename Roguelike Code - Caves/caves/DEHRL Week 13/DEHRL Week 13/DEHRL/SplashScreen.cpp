#include "stdafx.h"
#include "SplashScreen.h"
#include "Text.h"
#include "DEHGE.h"
#include "ScreenManager.h"
#include "Constants.h"
#include "Image.h"
// splash screen is more complicated than the others, since it
// needs to time out, or wait for a key press or mouse click before moving to the next
// screen
SplashScreen::SplashScreen()
{
	// reset the amount of time the splash screen ahs been up.
	timeShown = 0;
}


SplashScreen::~SplashScreen()
{
}

// which screen is this
ScreenID SplashScreen::getID()
{
	return ScreenID::SPLASH_SCREEN;
}

//add the text, and then connect us to the game engine
void SplashScreen::initialize()
{
	// add the title
	Text *t = new Text();
	t->setText("Roguelike");
	t->setPosition(50, 5);
	t->useOffset(false);
	Image *i = new Image();
	i->setImage("Dragon.txt");
	i->setPosition(0, 3);
	i->useOffset(false);
	DEHGE::getInstance()->addView(getID(), i);
	Image *i2 = new Image();
	i2->setImage("Knight.txt");
	i2->setPosition(65, 17);
	i2->useOffset(false);
	DEHGE::getInstance()->addView(getID(), i2);
	// and start getting events from the game engine
	DEHGE::getInstance()->addView(getID(), t);
	DEHGE::getInstance()->addModel(getID(), this);
	DEHGE::getInstance()->addKeyController(getID(), this);
	DEHGE::getInstance()->addMouseController(getID(), this);
}

// time has passed
void SplashScreen::update(int milliseconds)
{
	timeShown += milliseconds; // accumulate it
	if (timeShown > SPLASHTIME) 
	{
		// after 5 seconds, show the menu screen
		ScreenManager::getInstance()->pushScreen(ScreenID::MENU_SCREEN);
	}
}

// if a key is pressed, show the menu screen
void SplashScreen::keyPress(int key)
{
	ScreenManager::getInstance()->pushScreen(ScreenID::MENU_SCREEN);
}

// if the mouse is clicked, show the menu screen.
void SplashScreen::leftMouseDown(int x, int y)
{
	ScreenManager::getInstance()->pushScreen(ScreenID::MENU_SCREEN);
}