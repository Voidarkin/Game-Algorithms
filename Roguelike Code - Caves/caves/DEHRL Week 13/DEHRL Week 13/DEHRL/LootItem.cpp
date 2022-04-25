#include "stdafx.h"
#include "LootItem.h"
#include "DEHRender.h"
#include "Dungeon.h"
#include "Player.h"
#include <sstream>
// item that can be collected by the player
LootItem::LootItem(Item *i)
{
	item = i;
}

LootItem::~LootItem()
{
}

void LootItem::render()
{
	if (!visible)
	{
		return;
	}
	DEHRender::getInstance()->drawChar(position->getX(), position->getY(), '?', true);
}

// if the player steps on it, pick it up.
void LootItem::fireTrigger(Creature * c)
{
	Player *p = Dungeon::getInstance()->getPlayer();
	if (c != p)
	{
		return;
	}
	p->addItem(item);
	std::stringstream s;
	s << p->getName() << " found " << item->getDescription() << ".";
	Dungeon::getInstance()->getStatusBar()->setMessage(s.str());
	Dungeon::getInstance()->getCurrentMap()->removeTrigger(this);
}

TriggerTypes LootItem::getTriggerType()
{
	return TriggerTypes::ITEM;
}

bool LootItem::isWalkable(int x, int y)
{
	return false;
}