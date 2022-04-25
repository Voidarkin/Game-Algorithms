#include "stdafx.h"
#include "StandardAIStrategy.h"
#include "Dungeon.h"
#include "Creature.h"
#include "MoveCommand.h"
#include "HurtAIStrategy.h"
#include "PathAIStrategy.h"
StandardAIStrategy::StandardAIStrategy()
{
}


StandardAIStrategy::~StandardAIStrategy()
{
}

void StandardAIStrategy::dealWithPlayer()
{
	int px = Dungeon::getInstance()->getPlayer()->getX();
	int py = Dungeon::getInstance()->getPlayer()->getY();
	int dx = px - creature->getX();
	int dy = py - creature->getY();
	MoveCommand *com = new MoveCommand(); // moving onto the player will effectively do an attack
	com->setDirection(dx, dy);
	com->setCreature(creature);
	creature->getQueue()->push(com);
	// now, check to see if we're on the edge of dying...
	if (creature->getHP() < 2)
	{
		HurtAIStrategy *hurt = new HurtAIStrategy();
		hurt->setCreature(creature);
		creature->setStrategy(hurt);
	}
}

int StandardAIStrategy::getTargetX()
{
	return Dungeon::getInstance()->getPlayer()->getX();
}

int StandardAIStrategy::getTargetY()
{
	int currX = creature->getX();
	int currY = creature->getY();
	// did we move since last time?
	if (currX == prevX && currY == prevY)
	{
		// no, but we may be in combat
		int px = Dungeon::getInstance()->getPlayer()->getX();
		int py = Dungeon::getInstance()->getPlayer()->getY();
		int dx = px - creature->getX();
		int dy = py - creature->getY();
		if (dx*dx + dy*dy != 1) // no, we're not near the player
		{
			timestanding++;
			if (timestanding == 3)
			{
				timestanding = 0; // reset, in case we come back here
				PathAIStrategy *ps = new PathAIStrategy();
				creature->setStrategy(ps);
				ps->setCreature(creature);
			}
		}
		else
		{
			prevX = currX;
			prevY = currY;
			timestanding = 0;
		}
	}
	else
	{
		prevX = currX;
		prevY = currY;
		timestanding = 0;
	}
	return Dungeon::getInstance()->getPlayer()->getY();
}

void StandardAIStrategy::setCreature(Creature * c)
{
	AIStrategy::setCreature(c);
	timestanding = 0;
}
