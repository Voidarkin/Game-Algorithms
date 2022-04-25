#include "stdafx.h"
#include "Gold.h"
#include "Dungeon.h"
#include "DEHRender.h"
#include <sstream>
// pile of gold on the floor
Gold::Gold(int gp)
{
	amount = gp;
}


Gold::~Gold()
{
}

//draw the gold
void Gold::render()
{
	if (!visible)
	{
		return;
	}
	DEHRender::getInstance()->drawChar(position->getX(), position->getY(), '$', true);
}

// pick up th eogld (if the player)
void Gold::fireTrigger(Creature * c)
{
	Player *p = Dungeon::getInstance()->getPlayer();
	if (c != p)
	{
		return;
	}
	p->addGold(amount);
	std::stringstream s;
	s << p->getName() << " find " << amount << "gp.";
	Dungeon::getInstance()->getStatusBar()->setMessage(s.str());
	Dungeon::getInstance()->getCurrentMap()->removeTrigger(this);
}

// i am gold
TriggerTypes Gold::getTriggerType()
{
	return TriggerTypes::GOLD;
}

bool Gold::isWalkable(int x, int y)
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
