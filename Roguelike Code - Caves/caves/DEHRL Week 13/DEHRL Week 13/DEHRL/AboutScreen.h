#pragma once
#include "Screen.h"
// the screen that managed the about window
// has some text views, and a menu with an ok option on it.
class AboutScreen :
	public Screen
{
public:
	AboutScreen();
	virtual ~AboutScreen();

	// Inherited via Screen
	// return ScreenID::ABOUT_SCREEN
	virtual ScreenID getID();
	// add all the items to the screen
	virtual void initialize() override;
};