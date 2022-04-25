#include "stdafx.h"
#include "RunCommand.h"
#include "Creature.h"
#include "Dungeon.h"
RunCommand::RunCommand()
{
}


RunCommand::~RunCommand()
{
}

void RunCommand::execute()
{
	int oldX = creature->getX();
	int oldY = creature->getY();
	MoveCommand::execute();
	int newX = creature->getX();
	int newY = creature->getY();
	if (oldX == newX && oldY == newY)
	{
		return; // we didn't go anywhere.
	}
	if (somethingInteresting(newX, newY))
	{
		return;
	}
	// check the 4 directions around us.  Don't bother with the old spot.
	// up
	if (oldX != newX || oldY != newY - 1)
	{
		if (somethingInteresting(newX, newY - 1))
		{
			return;
		}
	}
	// down
	if (oldX != newX || oldY != newY + 1)
	{
		if (somethingInteresting(newX, newY + 1))
		{
			return;
		}
	}
	// left
	if (oldX != newX-1 || oldY != newY)
	{
		if (somethingInteresting(newX-1, newY))
		{
			return;
		}
	}
	// right
	if (oldX != newX+1 || oldY != newY)
	{
		if (somethingInteresting(newX+1, newY))
		{
			return;
		}
	}
	creature->getQueue()->push(this);
}

bool RunCommand::somethingInteresting(int ix, int iy)
{
	Creature * c = Dungeon::getInstance()->getCurrentMap()->getCreatureAt(ix, iy);
	if (c != NULL && c!= creature)
	{
		return true;
	}
	if (Dungeon::getInstance()->getCurrentMap()->getTriggerAt(ix, iy) != NULL)
	{
		return true;
	}	
	return false;
}
