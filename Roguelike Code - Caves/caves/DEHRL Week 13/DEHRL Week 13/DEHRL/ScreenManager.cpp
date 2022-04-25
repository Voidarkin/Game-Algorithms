#include "stdafx.h"
#include "ScreenManager.h"


ScreenManager* ScreenManager::instance = NULL;

// lazy access to the instance
ScreenManager * ScreenManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new ScreenManager();
	}
	return instance;
}

ScreenManager::ScreenManager()
{
}

ScreenManager::~ScreenManager()
{
}

// add a screen to the global list of screens
// maps work like arrays, but with things other than integers (possibly) as keys
void ScreenManager::addScreen(Screen *screen)
{
	allScreens[screen->getID()] = screen;
}

// switch to a particular screen.  this does NOT put it on the stack of screens...
// use only when you don't need to go back
void ScreenManager::setScreen(ScreenID id)
{
	currentScreenID = id;
}

//push a new screen onto the stack, making it the visible one
void ScreenManager::pushScreen(ScreenID id)
{
	currentScreens.push(allScreens[id]);
	currentScreenID = id;
}

// remove a screen from the stack, making the previous screen the current one
void ScreenManager::popScreen()
{
	currentScreens.pop();
	currentScreenID = currentScreens.top()->getID();
}

// find a screen, given it's id
Screen *ScreenManager::getScreen(ScreenID id)
{
	return allScreens[id];
}

// what screen is currently being shown
ScreenID ScreenManager::getCurrentScreenID()
{
	return currentScreenID;
}

// used at screen creation and init time to let sub entities know which one is underway,
// this clears the initializing screen value
void ScreenManager::doneInitializingScreen()
{
	initializingScreenID = ScreenID::MAX_SCREEN_ID;
}

// which screen is undergoing initalization
ScreenID ScreenManager::getInitializingScreenID()
{
	return initializingScreenID;
}

// specify which screen is undergoing initialization
void ScreenManager::startInitializingScreenID(ScreenID id)
{
	initializingScreenID = id;
}