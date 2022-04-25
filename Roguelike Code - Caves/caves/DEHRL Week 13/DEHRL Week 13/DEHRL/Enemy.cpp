#include "stdafx.h"
#include "Enemy.h"
#include "DEHRender.h"
#include "Dungeon.h"
#include "CombatManager.h"
#include <thread>
#include <Windows.h>
#include "Gold.h"
#include "Item.h"
#include "LootItem.h"
#include "ItemFactory.h"
#include "TerminatorAI.h"
// Enemy is anything chasing you around the dungeon
Enemy::Enemy()
{
	displayCharacter = ' ';
	proxy = NULL;
	frameDelay = 500; // move twice a second. Will be overwritten by creature factory
	active = false;
	equipment = new Entity(ComponentType::ENEMY_ENTITY);
}

Enemy::~Enemy()
{
	// when we go away, we need to clean up the visible proxy that is tied to us.
	if (proxy != NULL)
	{
		Dungeon::getInstance()->getCurrentMap()->getModel()->removeEnemyProxy(proxy);
	}
	// and possibly drop some loot...
	// 2 in 3 of dropping loot based on the monsters hp.
	int r = rand() % 3;
	if (r != 0)
	{
		Gold *g = new Gold((getHitDice()+1)*(rand()%10+1));
		g->setPosition(position);
		Dungeon::getInstance()->getCurrentMap()->addTrigger(g);
		g->makeVisible();
	}
	else // and the other 1 in 3 we drop an item
	{
		Item *i = ItemFactory::getInstance()->generateItem(Dungeon::getInstance()->getMapLevel());
		LootItem *li = new LootItem(i);
		li->setPosition(position);
		Dungeon::getInstance()->getCurrentMap()->addTrigger(li);
		li->makeVisible();
	}
}

// move the enemy.  Note - this is being called by the thread's run method, NOT by
// the game engine
void Enemy::update(int milliseconds)
{
	Creature::update(milliseconds); // clean up any outstanding commands

}

// draw the enemy - if we've seen it already
void Enemy::render()
{
	if (visible)
	{
		DEHRender::getInstance()->drawChar(position->getX(), position->getY(), displayCharacter, true);
	}
}

// when making a creature visible, we need to do two things.
// start the thread that will move this guy around, and create the proxy that the
// game engine will render in it's main game loop thread.
void Enemy::makeVisible()
{
	if (visible)
	{
		return; // already live - don't do it again.
	}
	Creature::makeVisible(); // we want to invoke the parent class version of makeVisible. This is how.
	// now that we are visible, we need a proxy thingy with a queue between us
	EnemyStateMessageQueue *queue = new EnemyStateMessageQueue();
	addObserver(queue);
	proxy = new EnemyProxy(displayCharacter, getX(), getY(), queue);
	Dungeon::getInstance()->getCurrentMap()->getModel()->addEnemyProxy(proxy);
	// we also want to start executing in our own thread of exection, so...
	active = true;
	TerminatorAI *ai = new TerminatorAI(this);
	t = new std::thread(&TerminatorAI::run, ai);

}

// Accessor
void Enemy::setChar(char c)
{
	displayCharacter = c;
}

// attempt to move the enemy
void Enemy::moveTo(int theX, int theY)
{
	int dx = 0;
	int dy = 0;
	int x = position->getX();
	int y = position->getY();
	// compute direction we want to move in
	if (theX < x)
	{
		dx = -1;
	}
	else if (theX > x)
	{
		dx = 1;
	}

	if (theY < y)
	{
		dy = -1;
	}
	else if (theY > y)
	{
		dy = 1;
	}
	// can we move there? Cannot walk through things we don't want to, and can't walk on other creatures
	if (Dungeon::getInstance()->getCurrentMap()->isWalkable(x + dx, y + dy))
	{
		setPosition(x + dx, y + dy);
	}
	else {
		if (Dungeon::getInstance()->getCurrentMap()->isWalkable(x + dx, y))
		{
			setPosition(x + dx, y);
		}
		// how about vertically
		if (Dungeon::getInstance()->getCurrentMap()->isWalkable(x, y + dy))
		{
			setPosition(x, y + dy);
		}
	}
	// once we've moved, we need to let the proxy know.  It may discard many of these messages
	// if we send them too fast, but that's ok. We do this by notifying everything (which
	// includes the message queue to the proxy)
	EnemyState *s = new EnemyState(getX(), getY());
	notifyObservers( s);
}

void Enemy::move(int dx, int dy)
{
	int x = position->getX() + dx;
	int y = position->getY() + dy;
	// is there a creature where we want to move?
	Player *p = Dungeon::getInstance()->getPlayer();
	if (p->getX() != x || p->getY() != y)
	{
		setPosition(x, y);
		EnemyState *s = new EnemyState(getX(), getY());
		notifyObservers(s);
	}
	// otherwise, hit it
	else
	{
		CombatManager::getInstance()->processCreatureAttack(this);
	}
}

// if we are near the player, use the combat manager to attack
void Enemy::attackPlayer()
{
	CombatManager::getInstance()->processCreatureAttack(this);
}

// method called by the thread - the active flag is there so that eventually, we'll be able to
// stop and restart the thread when the player switches levels.  At the moment, this doesn't
// happen yet... We need a set method to toggle active, and code when moving levels to set that
// value, and to restart the thread.
void Enemy::run()
{
	while (getHP() >0)
	{
		if (active)
		{
			update(frameDelay);
		}
		Sleep(frameDelay);
	}
	delete this;
}

// how fast does it move - i.e. how many milliseconds between moves
void Enemy::setFrameDelay(int f)
{
	frameDelay = f;
}

int Enemy::getFrameDelay()
{
	return frameDelay;
}

// put this thread on pause
void Enemy::pauseThread()
{
	active = false;
}

// resume this thread
void Enemy::resumeThread()
{
	active = true;
}

bool Enemy::isActive()
{
	return active;
}

// we are enemy
CreatureType Enemy::getCreatureType()
{
	return CreatureType::ENEMY;
}