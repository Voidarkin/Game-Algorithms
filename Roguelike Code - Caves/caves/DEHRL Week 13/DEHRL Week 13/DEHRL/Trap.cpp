#include "stdafx.h"
#include "Trap.h"
#include "DEHRender.h"
#include "Dungeon.h"
#include "ScreenManager.h"
// something that damages things that walk on them
Trap::Trap()
{
}

Trap::~Trap()
{
}

// draw the trap
void Trap::render()
{
	if (!visible)
	{
		return;
	}
	DEHRender::getInstance()->drawChar(position->getX(), position->getY(), (hasSeen ? '^' : ','), true);

}
// execute the trap
void Trap::fireTrigger(Creature * c)
{
	// this is here to avoid instagibbing the player. needs to go
	if ((rand() % 25) != 0)
	{
		return;
	}
	Player *p = Dungeon::getInstance()->getPlayer();
	// Damage creature
	if (c->applyDamage(1))
	{
		// the creture died.  was it the player? or a monster
		Dungeon::getInstance()->getStatusBar()->setMessage(c->getName() + " triggered a trap, and died.");
		if (c == p)
		{
			ScreenManager::getInstance()->setScreen(ScreenID::GAME_OVER_SCREEN);
		}
	}
	else
	{
		Dungeon::getInstance()->getStatusBar()->setMessage(c->getName() + " triggered a trap, but survived.");
		visible = true;
	}
}

// i am trap
TriggerTypes Trap::getTriggerType()
{
	return TriggerTypes::TRAP;
}

bool Trap::isWalkable(int x, int y)
{
	if (getX() == x && getY() == y)
	{
		return true;
	}
	return false;
}

// you can search for a trap, or disarm it
void Trap::applyPlayerAction(PlayerCommands command, int x, int y)
{
	if (command == PlayerCommands::SEARCH)
	{
		searchForTrap(x, y);
	}
	if (command == PlayerCommands::DISARM)
	{
		tryToDisarmTrap(x, y);
	}
}

// did I find it
void Trap::searchForTrap(int theX, int theY)
{
	int x = position->getX();
	int y = position->getY();
	if (x == theX && (y == (theY - 1) || y == (theY + 1)))
	{
		foundTrap();
	}
	if (y == theY && (x == (theX - 1) || x == (theX + 1)))
	{
		foundTrap();
	}
}

// yes I did
void Trap::foundTrap()
{
	hasSeen = true;
	Dungeon::getInstance()->getStatusBar()->setMessage("You can clearly see the trap.");
}

// red wire or blue wire
void Trap::tryToDisarmTrap(int theX, int theY)
{
	int r = rand() % 3;
	if (r != 0)
	{
		return; // failed to disarm it
	}
	int x = position->getX();
	int y = position->getY();
	if (x == theX && (y == (theY - 1) || y == (theY + 1)))
	{
		disarmTrap();
	}
	if (y == theY && (x == (theX - 1) || x == (theX + 1)))
	{
		disarmTrap();
	}
}

// corect wire found
void Trap::disarmTrap()
{
	Dungeon::getInstance()->getStatusBar()->setMessage("You disarm the trap.");
	Dungeon::getInstance()->getCurrentMap()->removeTrigger(this);
}