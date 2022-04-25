#include "stdafx.h"
#include "Menu.h"
#include "MenuModel.h"
#include "MenuController.h"
// base menu code
Menu::Menu()
{
	// set up the menu model and controller for the menu.
	model = new MenuModel();
	MenuController *mc = new MenuController(model);
}

Menu::~Menu()
{
}