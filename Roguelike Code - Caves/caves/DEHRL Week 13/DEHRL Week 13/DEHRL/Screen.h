#pragma once
#include "Constants.h"
// abstract base class for all the distinct screens in the game.
// a screen relates to a set of things that can be updated, controlled, and rendered
class Screen
{
public:
	Screen();
	virtual ~Screen();
	// what screen is this? Subclasses must decide
	virtual ScreenID getID() = 0;
	// subclasses will override this to do their own setup.
	virtual void initialize() = 0;
	// called by the screen manager, it does some setup, then called initialize
	void init();
};