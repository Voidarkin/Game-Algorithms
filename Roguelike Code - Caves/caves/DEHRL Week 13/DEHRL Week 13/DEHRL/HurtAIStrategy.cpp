#include "stdafx.h"
#include "HurtAIStrategy.h"


HurtAIStrategy::HurtAIStrategy()
{
}


HurtAIStrategy::~HurtAIStrategy()
{
}


void HurtAIStrategy::dealWithPlayer()
{
	Dungeon::getInstance()->getStatusBar()->setMessage("Please don't hurt me...");

}

int HurtAIStrategy::getTargetX()
{
	if (creature->getHP() < creature->getMaxHP())
	{
		creature->applyDamage(-1); // heal one hit point - every time we whimper, we get better...
	}
	else
	{
		// we are fully healed.  Time to kick some butt again. or whatever we started out doing
		creature->setStrategy(creature->getDefaultStrategy());
	}
	// we want to move away from the player if at all possible.
	int px = Dungeon::getInstance()->getPlayer()->getX();
	int cx = creature->getX();

	int dx = px - cx;
	// that is the direction we want to be moving in.  Lets set where we want to be the exact opposite.
	return cx - dx;
}

int HurtAIStrategy::getTargetY()
{
	// we want to move away from the player if at all possible.
	int py = Dungeon::getInstance()->getPlayer()->getY();
	int cy = creature->getY();

	int dy = py - cy;
	// that is the direction we want to be moving in.  Lets set where we want to be the exact opposite.
	return cy - dy;
}
