#include "stdafx.h"
#include "MapModel.h"
#include "Model.h"
#include "CreatureFactory.h"
#include "EnemyProxy.h"
// mapmodel is mostly empty - subclasses will do the heavy lifting.
MapModel::MapModel()
{
	triggers = new std::vector<Trigger *>();
	creatures = new std::vector<Creature *>();
	// the visible proxies
	enemies = new std::vector<EnemyProxy *>();
}

MapModel::~MapModel()
{
}

// at the start of the update, if we've got pending add/removes on triggers, process them.
// then give all the autonomous creatures some cpu time
// we have to do adds and removes in two stages if we're iterating over the list we
// want to modify
void MapModel::update(int milliseconds)
{
	if (triggersToRemove.empty() == false)
	{
		for each (Trigger *t in triggersToRemove)
		{
			reallyRemoveTrigger(t);
		}
		triggersToRemove.clear();
	}
	if (triggersToAdd.empty() == false)
	{
		for each (Trigger *t in triggersToAdd)
		{
			reallyAddTrigger(t);
		}
		triggersToAdd.clear();
	}
	for each (EnemyProxy *e in (*enemies))
	{
		e->update(milliseconds);
	}

	Player *p = Dungeon::getInstance()->getPlayer();
	if (p != NULL)
	{
		// finally, run any triggers on the player and creatures
		for each (Trigger *t1 in (*triggers))
		{
			if (t1->getX() == p->getX() && t1->getY() == p->getY())
			{
				t1->fireTrigger(p);
			}
			// this is no longer needed - whena creature moves, the room will update all the
			// triggers for the creature
			//for each (Creature *c in (*creatures))
			//{
			//	if (c->isVisible() && t1->getX() == c->getX() && t1->getY() == c->getY())
			//	{
			//		t1->fireTrigger(c);
			//	}
			//}
		}
	}
	// finally, try to remove any dead creatures from the list if they are still in there.
	// we cannot iterate over the creature list, and modify it while we do so, so copy the
	// pointers, then iterator over the copy and clear things immediately afterwards.
	std::vector<Creature *> corpses;
	for each (Creature *c in (*creatures))
	{
		if (c->getHP() <= 0)
		{
			corpses.push_back(c);
		}
	}
	for each (Creature *corpse in corpses)
	{
		removeCreature(corpse);
	
	}
	corpses.clear();
	for each (Creature *cr in (*creatures))
	{
		cr->update(milliseconds);
	}
}

// triggers can be on all map types, so makes sense to be able to add them
// at this level - this is a deferred add
void MapModel::addTrigger(Trigger * t)
{
	triggersToAdd.push_back(t);
}

// the real addition of a trigger.  called either by update, or by thigns that won't
// break if they modify the list of triggers
void MapModel::reallyAddTrigger(Trigger * t)
{
	triggers->push_back(t);
}

// generically, moving the player does nothing.  some map models care though
void MapModel::visit(int x, int y)
{
}

// generically, we're going to add 1-5 creatures per level.
// some of those creatures come in swarms though...
void MapModel::spawnCreatures(int level)
{
	int numToAdd = rand() % 5 + 1; // note - some mosnter types are... numerous...
	for (int i = 0; i < numToAdd; i++)
	{
		CreatureFactory::getInstance()->spawnMonster(level);
	}
}
// add a creature to the list of creatures.
// we need a way to kill them off later as well
void MapModel::addCreature(Creature * c)
{
	auto it = std::find(creatures->begin(), creatures->end(), c);
	if (it == creatures->end())
	{
		creatures->push_back(c);
	}
}

// needed if we want to kill creatures
void MapModel::removeCreature(Creature * c)
{
	auto it = std::find(creatures->begin(), creatures->end(), c);
	if (it != creatures->end())
	{
		creatures->erase(it);
	}
	delete c;
}

//Accessor 
std::vector<Creature*>* MapModel::getCreatures()
{
	return creatures;
}

std::vector<EnemyProxy*>* MapModel::getEnemies()
{
	return enemies;
}

// accessor
std::vector<Trigger*> *MapModel::getTriggers()
{
	return triggers;
}

// if there is as trigger in this location, return it, otherwise, return NULL
Trigger * MapModel::getTriggerAt(int x, int y)
{
	for each (Trigger *t in (*triggers))
	{
		if (t->getX() == x && t->getY() == y)
		{
			return t;
		}
	}
	return NULL;
}

// keep track of the stairs, and add it to the triggers
void MapModel::addStairsDown(StairsDown * stairs)
{
	stairsDown = stairs;
	addTrigger(stairs);
}

//Accessor 
StairsDown * MapModel::getStairsDown()
{
	return stairsDown;
}

// keep track of the stairs, and add it to the triggers
void MapModel::addStairsUp(StairsUp * stairs)
{
	stairsUp = stairs;
	addTrigger(stairs);
}

//Accessor 
StairsUp * MapModel::getStairsUp()
{
	return stairsUp;
}

// generically, we don't know what we want to happen with a particular command
// so let the triggers sort it out
void MapModel::processCommand(PlayerCommands command, int x, int y)
{
	// generically, ask the triggers to deal with the player command
	for each (Trigger *t in (*triggers))
	{
		t->applyPlayerAction(command, x, y);
	}
}

// request deferred removal of a trigger
void MapModel::removeTrigger(Trigger * t)
{
	triggersToRemove.push_back(t);
}

// immediate removal of a trigger - typically called from update.
void MapModel::reallyRemoveTrigger(Trigger * t)
{
	// removing things from vectors is a pain in the ass
	auto it = std::find(triggers->begin(), triggers->end(), t);
	if (it != triggers->end())
		triggers->erase(it);
}

// is there a creature at x, y?
Creature * MapModel::getCreatureAt(int x, int y)
{
	for each (Creature *c in (*creatures))
	{
		if (c->getX() == x && c->getY() == y)
		{
			return c;
		}
	}
	return NULL;
}

// add the main thread proxy for the creature to the model
void MapModel::addEnemyProxy(EnemyProxy * e)
{
	enemies->push_back(e);
}

// remove a main thread proxy from the model.  Invoked when the creature is
// destroyed
void MapModel::removeEnemyProxy(EnemyProxy * e)
{
	auto it = std::find(enemies->begin(), enemies->end(), e);
	if (it != enemies->end())
	{
		enemies->erase(it);
	}
}

bool MapModel::isCaveMapModel()
{
	return false;
}
