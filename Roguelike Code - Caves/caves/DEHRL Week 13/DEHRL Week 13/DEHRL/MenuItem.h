#pragma once
#include "MouseController.h"
#include "KeyController.h"
#include "Model.h"
#include "View.h"
#include "Constants.h"
#include <string>
#include "Command.h"
// base class for user menu items. This looks complicated, but it's pretty straight forward
class MenuItem :
	public MouseController, public KeyController, public Model, public View
{
public:
	MenuItem();
	~MenuItem();
	// set position and size of the menu item
	void init(int theX, int theY, int w, int h);
	// This will be called to set the command for the menu item
	virtual void initialize(Command *c);
	// what is displayed in the middle of the menu item.
	// note - text will auto center in both x and y directions
	void setText(std::string t);
	// called mostly by menu controller to change the state of a menu item, can also be called
	// internally when menu items are activated
	void setState(MenuItemState theState);
	// Inherited via KeyController
	// watching for space and enter keys to activate a menu item
	virtual void keyPress(int key);

	// Inherited via Model
	// this is here so we can do interesting things over time with menu items,
	// such as having the ability to scroll the text in them
	virtual void update(int milliseconds);

	// Inherited via View
	//draw the menu item as a rectangle with text inside of it.
	virtual void render();

	// from mouse controller
	// verify that the mouse was released over the same menu item it was pressed in
	// note - since we're only handling one event each frame, menu items may be slow to respond.
	// click slower.
	virtual void leftMouseUp(int x, int y);
	// look to see if the mouse down happened over this item, and change it's state to pressed
	virtual void leftMouseDown(int x, int y);

	// where the work done by the menu item takes place
	virtual void performAction();
	// helper method that tells us if a particular location is contained inside the menu item
	bool inside(int x, int y);
private:
	// the comamnd to run
	Command *command;
	// top left corner of the menu item
	int x;
	int y;
	// size of the menu item
	int width;
	int height;
	// what to display in it
	std::string text;
	// what state is it in now (will change rendering and click handling)
	MenuItemState state;
};