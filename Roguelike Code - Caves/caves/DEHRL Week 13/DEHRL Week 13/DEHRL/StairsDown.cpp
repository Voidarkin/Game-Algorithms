#include "stdafx.h"
#include "StairsDown.h"
#include "DEHRender.h"
#include "Dungeon.h"
// stairs down is a trigger that will eventually add a message to the 
// status bar, and allows the player to move to a deeper dungeon level

StairsDown::StairsDown()
{
}

StairsDown::~StairsDown()
{
}

// stairs down look like >
void StairsDown::render()
{
	if (!visible)
	{
		return;
	}
	DEHRender::getInstance()->drawChar(position->getX(), position->getY(), '>', true);
}

// eventually, if the crature that stepped on the trigger is the player,
// then add a status bar message
void StairsDown::fireTrigger(Creature * c)
{
	if (c == Dungeon::getInstance()->getPlayer())
	{
		Dungeon::getInstance()->getStatusBar()->setMessage("You see stairs down. (hit > to move down)");
	}
}

// this is stairs down
TriggerTypes StairsDown::getTriggerType()
{
	return TriggerTypes::STAIRS_DOWN;
}

// if asked can we walk somewhere, if it's our location, yes.  otherwise
// we don't know
bool StairsDown::isWalkable(int x, int y)
{
	if (position->getX() == x && position->getY() == y)
	{
		return true;
	}
	else
	{
		return false;
	}
}