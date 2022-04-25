#pragma once
#include "Menu.h"
// the menu on the menu screen that contains the three menu items
class MenuScreenMenu :
	public Menu
{
public:
	MenuScreenMenu();
	virtual ~MenuScreenMenu();

	// Inherited via Menu
	// create and add the menu items
	virtual void initialize();
};