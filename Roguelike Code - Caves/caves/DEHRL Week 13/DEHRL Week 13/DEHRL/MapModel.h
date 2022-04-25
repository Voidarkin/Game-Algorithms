#pragma once
#include "Model.h"
#include "Point.h"
#include "Trigger.h"
#include "StairsDown.h"
#include "StairsUp.h"
#include <vector>
#include "Creature.h"
#include "EnemyProxy.h"

// Map model is an abstract base class for individual dungeon level types to start with
class MapModel :
	public Model
{
public:
	MapModel();
	virtual ~MapModel();
	// allow the map to update itself
	virtual void update(int milliseconds);
	// maps must provide a way to find empty space on them.
	// how they do it is subclass specific.
	virtual Point *getRandomEmptySpace()=0;
	// triggers are generic enough that we can keep track of them in the top level of the
	// map model.  This adds a trigger at the start of the next update cycle
	virtual void addTrigger(Trigger *t);
	// return the vector of triggers
	// note thatg we're returning a POINTER to a vector of POINTERS
	// this avoids copying things back and forth
	std::vector<Trigger*> *getTriggers();	
	// return the trigger (or null) at a given location
	Trigger *getTriggerAt(int x, int y);
	// different types of map models will have different ways of knowing if something
	// can be walked on
	virtual bool isWalkable(int x, int y) = 0;
	// add a staircase down.  This will also add it to the list of triggers
	void addStairsDown(StairsDown *stairs);
	// find the stairs down
	StairsDown *getStairsDown();
	// add a staircase up. this will also add it to the list of triggers
	void addStairsUp(StairsUp *stairs);
	// find the stairs up
	StairsUp *getStairsUp();
	// deal with the player commands (search, open, close)
	virtual void processCommand(PlayerCommands command, int x, int y);
	// queue a trigger to be removed at the next update cycle
	virtual void removeTrigger(Trigger *t);
	// called at start of update, will remove all triggers that have been queued
	// for destruction
	void reallyRemoveTrigger(Trigger *t);
	// called at start of update, will add all triggers that have been queued for
	// addition
	void reallyAddTrigger(Trigger *t);
	// deal with fact that player has moved to x,y
	virtual void visit(int x, int y);
	// deal with moster spawning.  virtual in case some levels want spawning to work
	// differently
	virtual void spawnCreatures(int level);
	// add a creature to the vector of creatures on this level.  Once we can kill them
	// (or when they learn to use stairs), will also need remove creature
	virtual void addCreature(Creature *c);
	// remove a creature from the vectors. used when things die.
	virtual void removeCreature(Creature *c);
	// accessor
	std::vector<Creature *> *getCreatures();
	// accessor to the proxy list
	std::vector<EnemyProxy *> *getEnemies();
	// return the creature (or NULL) at the given X and Y
	// even if you can't see it yet...
	Creature *getCreatureAt(int x, int y);
	// accessor
	void addEnemyProxy(EnemyProxy *e);
	// accessor
	void removeEnemyProxy(EnemyProxy *e);
	virtual bool isCaveMapModel();
protected:
	// the list of triggers on this dungeon level
	std::vector<Trigger*> *triggers;
	// queue of triggers to get rid of in next update cycle
	std::vector<Trigger*> triggersToRemove;
	// queue of triggers to add in next update cycle
	std::vector<Trigger *> triggersToAdd;
	// all the creatures on this level
	std::vector<Creature *> *creatures;
	// the visible proxies for the enemies
	std::vector<EnemyProxy *> *enemies;
	// the stairs down
	StairsDown *stairsDown;
	// the stairs up
	StairsUp *stairsUp;
};