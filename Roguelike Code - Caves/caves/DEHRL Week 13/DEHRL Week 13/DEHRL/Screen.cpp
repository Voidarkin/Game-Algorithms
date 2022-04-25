#include "stdafx.h"
#include "Screen.h"
#include "ScreenManager.h"

Screen::Screen()
{
	
}


Screen::~Screen()
{
}

void Screen::init()
{
	// set things up so the init code in the subclasses can find out what is
	// initializing
	ScreenManager::getInstance()->startInitializingScreenID(getID());
	initialize(); // let the subclasses do their thing
	// and we're done the init stage
	ScreenManager::getInstance()->doneInitializingScreen();
}