#include "stdafx.h"
#include "MenuModel.h"
#include "DEHGE.h"
#include "ScreenManager.h"
MenuModel::MenuModel()
{
}

MenuModel::~MenuModel()
{
}

// genericly, menu models don't need updating
void MenuModel::update(int milliseconds)
{
}

// add a menu item to the list
void MenuModel::addMenuItem(MenuItem * item)
{
	// what screen are we on?
	ScreenID id = ScreenManager::getInstance()->getInitializingScreenID();
	//add it to the list of menu items
	items.push_back(item);
	// and tell the game engine about it
	DEHGE::getInstance()->addModel(id,item);
	DEHGE::getInstance()->addView(id,item);
	DEHGE::getInstance()->addKeyController(id,item);
	DEHGE::getInstance()->addMouseController(id,item);
	// if we only have one item, select it.
	if (items.size() == 1)
	{
		item->setState(MenuItemState::HOVER);
		selectedMenuItem = 0;
	}
}

// light up the next menu item, and turn off the others
void MenuModel::selectNextMenuItem()
{
	int size = items.size();
	selectedMenuItem = (selectedMenuItem + 1) % size; // will wrap back to zero
	for (int i = 0; i < size; i++)
	{
		if (i == selectedMenuItem) // if this is the selected item, light it up
		{
			items[i]->setState(MenuItemState::HOVER);
		}
		else
		{
			// if not, turn it off
			items[i]->setState(MenuItemState::UNSELECTED);
		}
	}
}

// light up the previous menu item, and turn off the others
void MenuModel::selectPreviousMenuItem()
{
	int size = items.size();
	selectedMenuItem = selectedMenuItem -1;
	if (selectedMenuItem == -1) // did we go past the first item, then loop around to the end
	{
		selectedMenuItem = size - 1;
	}
	for (int i = 0; i < size; i++)
	{
		if (i == selectedMenuItem) // if htis is the selected ite, light it up
		{
			items[i]->setState(MenuItemState::HOVER);
		}
		else // if not, turn it off
		{
			items[i]->setState(MenuItemState::UNSELECTED);
		}
	}
}

// if there is a menu item at this location, select it.  if a menu item is not here, unselect it.
void MenuModel::selectMenuItem(int x, int y)
{
	int size = items.size();
	for (int i = 0; i < size; i++)
	{
		MenuItem *item = items[i];
		// check to see if this point is inside the menu item
		if (item->inside(x, y))
		{
			//if so, light it up.
			items[i]->setState(MenuItemState::HOVER);
		}
		else
		{//if not, don't
			items[i]->setState(MenuItemState::UNSELECTED);
		}
	}
}

MenuItem * MenuModel::makeMenuItem()
{
	MenuItem *mi = new MenuItem();
	addMenuItem(mi);
	return mi;
}