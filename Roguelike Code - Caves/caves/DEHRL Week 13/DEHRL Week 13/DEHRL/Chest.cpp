#include "stdafx.h"
#include "Chest.h"
#include "DEHRender.h"
#include "Gold.h"
#include "Dungeon.h"
#include "Item.h"
#include "ItemFactory.h"
#include "LootItem.h"
// a gold filled chest
Chest::Chest()
{
}

Chest::~Chest()
{
}

// draw the chest
void Chest::render()
{
	// if we can't see it, don't draw it
	if (!visible)
	{
		return;
	}
	
	DEHRender::getInstance()->drawChar(position->getX(), position->getY(), '%', true);
}

// cannot open a chest you are standing on.
void Chest::fireTrigger(Creature * c)
{
	Dungeon::getInstance()->getStatusBar()->setMessage("You are standing on top of a chest, but will need to move to open it.");
}

TriggerTypes Chest::getTriggerType()
{
	return TriggerTypes::CHEST;
}

// this is not important, since the room will let you move there
bool Chest::isWalkable(int x, int y)
{
	return false;
}

// see fi they want to open me
void Chest::applyPlayerAction(PlayerCommands command, int x, int y)
{
	if (command == PlayerCommands::OPEN)
	{
		attemptToOpen(x, y);
	}
}

// are they close enough to open me?
void Chest::attemptToOpen(int theX, int theY)
{
	int x = position->getX();
	int y = position->getY();
	if (x == theX && (y == (theY - 1) || y == (theY + 1)))
	{
		openChest();
	}
	if (y == theY && (x == (theX - 1) || x == (theX + 1)))
	{
		openChest();
	}
}

// open me.
void Chest::openChest()
{
	Dungeon::getInstance()->getCurrentMap()->removeTrigger(this);
	// and replace ourselves with gold (2/3) or a loot item(1/3)
	int r = rand() % 3;
	if (r != 0)
	{
		Gold *g = new Gold((rand() % 10 + 1) *(rand() % 10 + 1)*(1 + Dungeon::getInstance()->getMapLevel()));
		g->setPosition(getX(), getY());
		g->makeVisible();
		Dungeon::getInstance()->getCurrentMap()->addTrigger(g);
		Dungeon::getInstance()->getStatusBar()->setMessage("You open the chest - it's full of gold...");
	}
	else
	{
		Item *i = ItemFactory::getInstance()->generateItem(Dungeon::getInstance()->getMapLevel());
		LootItem *li = new LootItem(i);
		li->setPosition(position);
		Dungeon::getInstance()->getCurrentMap()->addTrigger(li);
		li->makeVisible();
		Dungeon::getInstance()->getStatusBar()->setMessage("You open the chest - it had an item inside...");
	}
}