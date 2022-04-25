#include "stdafx.h"
#include "SecretDoor.h"
#include "Dungeon.h"
#include "Door.h"
#include "DEHRender.h"
// a door that remains hidden until you search for it.
SecretDoor::SecretDoor()
{
}

SecretDoor::~SecretDoor()
{
}

// not much to draw for a secret door - it's secret after all
void SecretDoor::render()
{
	// code in here was when I was testing them, and needed to see them.
	if (!visible)
	{
		return;
	}
	// in case it's at the end of a hallway
	DEHRender::getInstance()->drawChar(position->getX(), position->getY(), '#', true);

}

// secret doors don't do much
void SecretDoor::fireTrigger(Creature * c)
{
}

// I'm a secret door
TriggerTypes SecretDoor::getTriggerType()
{
	return TriggerTypes::SECRET_DOOR;
}

// can't walk on them until you find them
bool SecretDoor::isWalkable(int x, int y)
{
	return false;

}

// if the player tries to search, find out if they are near the secret door
void SecretDoor::applyPlayerAction(PlayerCommands command, int x, int y)
{
	if (command == PlayerCommands::SEARCH)
	{
		searchForDoor(x, y);
	}
}

// is the player near the door? If so, report it as found
void SecretDoor::searchForDoor(int theX, int theY)
{
	int x = position->getX();
	int y = position->getY();
	if (x == theX && (y == (theY - 1) || y == (theY + 1)))
	{
		foundDoor();
	}
	if (y == theY && (x == (theX - 1) || x == (theX + 1)))
	{
		foundDoor();
	}
}

// replace the secret door with a regular door
void SecretDoor::foundDoor()
{
	// might need to search several times to find the door.
	int d20 = rand() % 20;
	if (d20 == 1)
	{
		return;
	}
	if (d20 > Dungeon::getInstance()->getPlayer()->getHitDice())
	{
		return;
	}
	// first, we need to remove ourselves from the list of triggers
	Dungeon::getInstance()->getCurrentMap()->removeTrigger(this);
	// and replace ourselves with a door
	Door *d = new Door();
	d->setPosition(getX(), getY());
	d->makeVisible();
	Dungeon::getInstance()->getCurrentMap()->addTrigger(d);
}