#pragma once
#include "Screen.h"
#include "Constants.h"
#include <map>
#include <stack>
// Screen manager manages a collection of screens - both the entire set of screens as created,
// as well as keeping a stack of screens allowing for easy and fast navigation between them
class ScreenManager
{
public:
	// screen manager is a singleton
	static ScreenManager *getInstance();
	// add a new screen to the master list of screens
	void addScreen(Screen *screen);
	// jump directly to a given screen
	void setScreen(ScreenID id);
	// add a screen to the stack of screens
	void pushScreen(ScreenID id);
	// remove the top screen from the stack, showing the one below it
	void popScreen();
	// find a numbered screen
	Screen *getScreen(ScreenID id);
	// what screen id is currently active
	ScreenID getCurrentScreenID();
	// used at startup - this allows a screen to tell the system it is in startup, so that the
	// getInitializingScreenID will work
	void startInitializingScreenID(ScreenID id);
	// the currently initializing screen is done
	void doneInitializingScreen();
	// what screen is currently initializing.  The game engine needs this so it can put
	// what screen is in the middle of initializing - this lets views etc. that are being 
	// created by sub components to still be added correctly to the game engine
	ScreenID getInitializingScreenID();
private:
	// the one and only screen manager
	static ScreenManager *instance;
	ScreenManager();
	virtual ~ScreenManager();
	// the master list of all screens
	std::map<ScreenID, Screen *> allScreens;
	// the current display stack of screens - the one at the top will be the one displayed
	std::stack<Screen*> currentScreens;
	// what screen id is being displayed.  used by the game engine to pick the right
	// views, models and controllers to interact with
	ScreenID currentScreenID;
	// what screen is undergoing initialization right now.
	ScreenID initializingScreenID;
};