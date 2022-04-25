#include "stdafx.h"
#include "BatAIStrategy.h"
#include "Creature.h"
#include <windows.h>
#include "Dungeon.h"
#include "MoveCommand.h"
BatAIStrategy::BatAIStrategy()
{
}


BatAIStrategy::~BatAIStrategy()
{
}

void BatAIStrategy::dealWithPlayer()
{


	// if we are next to the player, and didn't just try to bit it, then
	// attack
	if (attackedAlready == false)
	{
		// Where is the player, relative to us? (calculate dx and dy)
		int px = Dungeon::getInstance()->getPlayer()->getX();
		int py = Dungeon::getInstance()->getPlayer()->getY();
		int dx = px - creature->getX();
		int dy = py - creature->getY();
		MoveCommand *com = new MoveCommand(); // moving onto the player will effectively do an attack
		com->setDirection(dx, dy);
		com->setCreature(creature);
		creature->getQueue()->push(com);
		attackedAlready = true;
	}
	else // otherwise, move and clear the fact that we tried to attack
	{
		attackedAlready = false;
	}
}

int BatAIStrategy::getTargetX()
{
	if (remainingMovesX <= 0)
	{
		remainingMovesX = rand() % 10;
		tx = creature->getX() + rand() % 11 - 5;
	}
	remainingMovesX--;
	return tx;
}

int BatAIStrategy::getTargetY()
{
	if (remainingMovesY <= 0)
	{
		remainingMovesY = rand() % 10;
		ty = creature->getY() + rand() % 11 - 5;
	}
	remainingMovesY--;
	return ty;
}

