#include "stdafx.h"
#include "MenuController.h"
#include "DEHGE.h"
#include "ScreenManager.h"
#include "Constants.h"

// the menu controller needs to save the model, and register as key and mouse controllers
// with the game engine.
MenuController::MenuController(MenuModel *model)
{
	menuModel = model;
	// we need the screen id that we're in the middle of configuring so that we
	// can tell the game engine where we live
	ScreenID id = ScreenManager::getInstance()->getInitializingScreenID();
	DEHGE::getInstance()->addKeyController(id, this);
	DEHGE::getInstance()->addMouseController(id, this);
}

MenuController::~MenuController()
{
}

// when a key is pressed
void MenuController::keyPress(int key)
{
	// only up and down matter, and they move to the previous and next menu items
	// respectively (with wrap around - but that's handled internally to the menu model)
	if (key == KeyboardMap::KM_UP)
	{
		menuModel->selectPreviousMenuItem();
	}
	if (key == KeyboardMap::KM_DOWN)
	{
		menuModel->selectNextMenuItem();
	}
}

// if the mouse moved, we might be overtop of a menu item - let the menu model sort that out
void MenuController::mouseMoved(int x, int y)
{
	menuModel->selectMenuItem(x, y);
}