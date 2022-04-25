#include "stdafx.h"
#include "Door.h"
#include "DEHRender.h"
#include "Dungeon.h"
#include "StatusBar.h"
#include "Room.h"
#include "Hallway.h"
// initially, doors are closed
Door::Door()
{
	open = false;
}

Door::~Door()
{
}

// draw the door
void Door::render()
{
	// if we can't see it, don't draw it
	if (!visible)
	{
		return; 
	}
	// open =
	// closed +
	DEHRender::getInstance()->drawChar(position->getX(), position->getY(), (open?'=':'+'), true);
}

// do something if someone is on the door
void Door::fireTrigger(Creature * c)
{
	// and now the magic begins.
	// find the rooms and hallways that this door is inside, and add this creature to them.
	Dungeon::getInstance()->getCurrentMap()->getModel()->addCreature(c);
	// we had to add it directly to the map model, not the map to avoid it being teleported randomly.
}

// we're a door
TriggerTypes Door::getTriggerType()
{
	return TriggerTypes::DOOR;
}

// if the door is open, and at the x and y coordinates, let them pass.
// otherwise, don't
bool Door::isWalkable(int x, int y)
{
	if (position->getX() == x && position->getY() == y)
	{
		return open;
	}
	else
	{
		return false;
	}
}

// If the player tries to open or close, and we're close enough,
// then open the door or close the door.
void Door::applyPlayerAction(PlayerCommands command, int x, int y)
{
	if (command == PlayerCommands::OPEN)
	{
		attemptToOpen(x, y);
	}
	if (command == PlayerCommands::CLOSE)
	{
		attemptToClose(x, y);
	}
}

// is there a nearby door we can open?
void Door::attemptToOpen(int theX, int theY)
{
	// when player tries to open a door, we need to be near to it.
	//  X 
	// XPX  P is player.  X is the spot this door could be to be affected.
	//  X
	int x = position->getX();
	int y = position->getY();
	// up and down
	if (x == theX && (y == (theY - 1) || y == (theY + 1)))
	{
		open = true;
		Dungeon::getInstance()->getCurrentMap()->visit(getX(), getY());
	}
	// left and right
	if (y == theY && (x == (theX - 1) || x == (theX + 1)))
	{
		open = true;
		Dungeon::getInstance()->getCurrentMap()->visit(getX(), getY());
	}
	// if we get to here, we are not near the door we are trying to open
}

void Door::attemptToClose(int theX, int theY)
{
	// when player tries to close a door, we need to be next to it.
	int x = position->getX();
	int y = position->getY();
	if (x == theX && (y == (theY - 1) || y == (theY + 1)))
	{
		open = false;
	}
	if (y == theY && (x == (theX - 1) || x == (theX + 1)))
	{
		open = false;
	}
	// if we get to here, we are not near the door we are trying to close
}

// accessor
bool Door::isOpen()
{
	return open;
}