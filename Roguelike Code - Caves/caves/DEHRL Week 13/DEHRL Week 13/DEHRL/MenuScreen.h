#pragma once
#include "Screen.h"
// the games main menu screen
class MenuScreen :
	public Screen
{
public:
	MenuScreen();
	virtual ~MenuScreen();

	// Inherited via Screen
	// return the main menu screen id
	virtual ScreenID getID();
	// add the menu main screen menu, and some text views
	virtual void initialize();
};