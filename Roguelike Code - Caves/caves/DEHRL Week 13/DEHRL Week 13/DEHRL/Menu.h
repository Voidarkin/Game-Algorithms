#pragma once
#include "MenuModel.h"
// A menu creates and contains a menu model, which has all the menu items in it. 
// it also creates a menu controller, which deals with things like up and down arrow keys,
// and mouse movement over menu items.
class Menu
{
public:
	Menu();
	virtual ~Menu();
	// subclasses will provide this method to set the specific menu items up
	virtual void initialize() = 0;
protected:
	// the model storing the menu items.
	// note - the order the items are added is the order that key navigatin will take.
	MenuModel *model;
};