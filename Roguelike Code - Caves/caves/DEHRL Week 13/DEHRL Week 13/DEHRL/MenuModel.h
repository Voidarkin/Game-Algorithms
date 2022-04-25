#pragma once
#include "Model.h"
#include "MenuItem.h"
#include <vector>
// the Menu model holds the menu items that make up a particular menu
// it keeps track of the active one, and the controller uses it to request changing
// the selection
class MenuModel :
	public Model
{
public:
	MenuModel();
	virtual ~MenuModel();

	// Inherited via Model
	// not used right now, but here in case we want to do things on a time basis
	virtual void update(int milliseconds);
	// add a menu item to the list of menu items.
	// the order they are added is the order that will be used when using up/down keys
	void addMenuItem(MenuItem *item);
	// select the next menu item in the list (will wrap around)
	void selectNextMenuItem();
	// select the previous menu item in the list (will wrap around)
	void selectPreviousMenuItem();
	// try to select a menu item at a given x and y (if there is one)
	void selectMenuItem(int x, int y);
	MenuItem *makeMenuItem();
private:
	// the list of menu items
	std::vector<MenuItem *> items;
	// which menu item in the list is currently selected
	int selectedMenuItem = 0;
};