#pragma once
#include "Menu.h"
// the menu on the about screen - it's got a single menu item,
// the ok button that pops you back to the menu screen
class AboutScreenMenu :
	public Menu
{
public:
	AboutScreenMenu();
	virtual ~AboutScreenMenu();

	// Inherited via Menu
	// will add the menu item to the menu model
	virtual void initialize();
};