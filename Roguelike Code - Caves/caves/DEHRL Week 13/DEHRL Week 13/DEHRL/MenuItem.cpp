#include "stdafx.h"
#include "MenuItem.h"
#include "DEHRender.h"
#include <string>

MenuItem::MenuItem()
{
}

MenuItem::~MenuItem()
{
}

// a menu item needs a position and a width, and starts out unselected
void MenuItem::init(int theX, int theY, int w, int h)
{
	x = theX;
	y = theY;
	width = w;
	height = h;
	
	state = MenuItemState::UNSELECTED;
}

// set the command that the menu item will run
void MenuItem::initialize(Command * c)
{
	command = c;
}

// define the text that shows up in a menu item
void MenuItem::setText(std::string t)
{
	text = t;
}

// setter for the state
void MenuItem::setState(MenuItemState theState)
{
	state = theState;
}

// hitting spacewill trigger the menu item, if it's in a hover or pressed state
void MenuItem::keyPress(int key)
{
	if (key != ' ')
	{
		return;
	}
	if (state == MenuItemState::HOVER || state == MenuItemState::PRESSED)
	{
		setState(MenuItemState::UNSELECTED);
		performAction(); // let the subclass override deal with this.
	}
}

// empty placeholder so subclasses don't need to supply one - unless they want to.
void MenuItem::update(int milliseconds)
{
}

// draw the menu item.  rectangle with text centered in it.
void MenuItem::render()
{
	// where does the text go
	int textLen = text.length();
	int textX = x + width / 2 - textLen / 2;
	int textY = y + height / 2;
	char c; // character to draw the rectangle with based on the state
	switch (state)
	{
	case MenuItemState::UNSELECTED:
		c = '=';
		break;
	case MenuItemState::PRESSED:
		c = '*';
		break;
	case MenuItemState::DISABLED:
		c = '.';
		break;
	case MenuItemState::HOVER:
		c = '#';
		break;
	}
	// and draw the rect and text
	DEHRender::getInstance()->drawRect(x, y, x + width-1, y + height-1, c);
	DEHRender::getInstance()->drawText(textX, textY, text);
}

// when mouse is released
void MenuItem::leftMouseUp(int mx, int my)
{
	// if this menu item hadn't been pressed, it's not for us
	if (state != MenuItemState::PRESSED)
	{
		return; // wasn't us
	}
	// is the coordinates of the mouse release inside this item?
	if (!inside(mx,my))
	{
		return; // released outside of us.
	}
	// run the menu item action
	performAction();
	// and clear the menu item state
	setState(MenuItemState::UNSELECTED);
}

// when mouse is pressed
void MenuItem::leftMouseDown(int x, int y)
{
	if (!inside(x, y)) // if it's not inside of us, we're not selected
	{
		setState(MenuItemState::UNSELECTED);
	}
	else
	{
		// it was over us, so switch to pressed
		setState(MenuItemState::PRESSED);
	}
}

// get the command to do it's thing
void MenuItem::performAction()
{
	command->execute();
}

// is the point inside the rectangle or not?
bool MenuItem::inside(int mx, int my)
{
	return !(mx <x || mx > x + width || my < y || my > y + height);
}