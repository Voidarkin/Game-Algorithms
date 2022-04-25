#pragma once
#include "Dungeon.h"

// the entry point for the actual application
// in this case, we create and initialize a dungeon, then let it loose.
class Application
{
public:
	Application();
	virtual ~Application();
	// perform whatever one time initialization of the game is required.
	void initialize();
};