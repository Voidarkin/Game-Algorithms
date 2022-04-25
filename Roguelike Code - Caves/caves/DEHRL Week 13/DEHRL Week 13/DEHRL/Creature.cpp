#include "stdafx.h"
#include "Creature.h"
#include "Dungeon.h"
// base class for all creatures 
Creature::Creature()
{
	position = new Point();
	// don't assume we can see it at the start
	visible = false;
}

Creature::~Creature()
{
}

// accessor
int Creature::getHP()
{
	return hp;
}

// accessor
int Creature::getMaxHP()
{
	return maxHP;
}

// accessor
int Creature::getX()
{
	return position->getX();
}

// accessor
int Creature::getY()
{
	return position->getY();
}

// accessor
void Creature::setPosition(Point * p)
{
	if (position != NULL) // avoid a memory leak
	{
		delete position;
	}
	position = p;
}

// accessor
Point * Creature::getPosition()
{
	return position;
}

// try to set the creature position, while keeping walkability under consideration
void Creature::setPosition(int theX, int theY)
{
	if (Dungeon::getInstance()->getCurrentMap()->isWalkable(theX, theY))
	{
		position->setPosition(theX, theY);

	}
}

// placeholder for now - will eventually try to move the creature by delta X and delta Y
// possibly resulting in an attack if that moves it onto the player
// or in some cases, attacking a monster
void Creature::move(int dx, int dy)
{
}

// accessor
void Creature::makeVisible()
{
	visible = true;
}

// sublcasses will override this to control how they move and what they do
void Creature::update(int milliseconds)
{
	if (queue != NULL)
	{
		int count = queue->count();
		for (int i = 0; i < count; i++)
		{
			CreatureCommand *command = queue->front();
			queue->pop();
			command->execute();
		}
	}
}

// subclasses responsible for drawing
void Creature::render()
{
}

// Accessor
void Creature::setDamage(int num, int dice)
{
	numberOfDamageDice = num;
	damageDice = dice;
}

// Accessor
void Creature::setHitDice(int hd)
{
	hitDice = hd;
}

int Creature::getHitDice()
{
	return hitDice;
}

// Accessor
void Creature::setAC(int armorClass)
{
	ac = armorClass;
}

int Creature::getAC()
{
	return ac;
}

// Accessor
void Creature::setName(std::string n)
{
	name = n;
}

std::string Creature::getName()
{
	return name;
}

// damage the creature.  returns true if this attack resulted in killing the creature.
bool Creature::applyDamage(int damage)
{
	hp -= damage;
	if (hp <= 0)
	{
		return true;
	}
	return false;
}

// is this creature currently visible
bool Creature::isVisible()
{
	return visible;
}

// add an observer to our list (if they are not already there)
void Creature::addObserver(CreatureObserver * observer)
{
	auto it = std::find(observers.begin(), observers.end(), observer);
	if (it == observers.end())
	{
		observers.push_back(observer);
	}

}

// remove an observer from our list
void Creature::removeObserver(CreatureObserver * observer)
{
	auto it = std::find(observers.begin(), observers.end(), observer);
	if (it != observers.end())
	{
		observers.erase(it);
	}
}

// tell all observers that something has changed
void Creature::notifyObservers(EnemyState * state)
{
	// we need a copy of our master list of observers.
	// this is because the act of notifying them may result in our
	// removing them, and that would break looping over all of them.
	std::vector<CreatureObserver *> toNotify;
	toNotify = observers;
	for each (CreatureObserver *observer in toNotify)
	{
		observer->notify(this, state);
	}
}

// accessor
Entity * Creature::getEquipment()
{
	return equipment;
}

CreatureCommandMessageQueue * Creature::getQueue()
{
	return queue;
}

void Creature::setQueue(CreatureCommandMessageQueue * q)
{
	queue = q;
}

AIStrategy * Creature::getDefaultStrategy()
{
	return defaultStrategy;
}

void Creature::setStrategy(AIStrategy * theStrategy)
{
	strategy = theStrategy;
	if (defaultStrategy == NULL)
	{
		defaultStrategy = theStrategy;
	}
}

AIStrategy * Creature::getStrategy()
{
	return strategy;
}

// also sets the starting hp to the max hp
void Creature::setMaxHP(int mhp)
{
	maxHP = mhp;
	hp = mhp;
}