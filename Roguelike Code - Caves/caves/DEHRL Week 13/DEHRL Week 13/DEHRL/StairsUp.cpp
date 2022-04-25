#include "stdafx.h"
#include "StairsUp.h"
#include "DEHRender.h"
#include "Dungeon.h"
StairsUp::StairsUp()
{
}

StairsUp::~StairsUp()
{
}

// if we can see it, it looks like <
void StairsUp::render()
{
	if (!visible)
	{
		return;
	}
	DEHRender::getInstance()->drawChar(position->getX(), position->getY(), '<', true);
}

void StairsUp::fireTrigger(Creature * c)
{
	if (c == Dungeon::getInstance()->getPlayer())
	{
		Dungeon::getInstance()->getStatusBar()->setMessage("You see stairs up. (hit < to move up)");
	}
}

// I am stairs up
TriggerTypes StairsUp::getTriggerType()
{
	return TriggerTypes::STAIRS_UP;
}

// and yes, you can stand on me
bool StairsUp::isWalkable(int x, int y)
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