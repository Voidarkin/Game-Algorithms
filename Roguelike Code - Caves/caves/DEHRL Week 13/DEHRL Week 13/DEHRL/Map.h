#pragma once
#include "MapModel.h"
#include "MapView.h"
#include "Point.h"
#include "StairsDown.h"
#include "StairsUp.h"
// the base class for all maps.  At it's simplest, a map has a model and a view
// associated with it, and represents a single dungeon level.
class Map
{
public:
	Map();
	virtual ~Map();
	// accessor for the Map Model
	MapModel *getModel();
	// accessor for the map view
	MapView *getView();
	// helper method.  This could be used when spawning loot, creatures etc.
	// we don't need to make this virtual, because we'll let the mapModel handle
	// the specifics of how to get an empty location
	Point *getRandomEmptySpace();
	// now that we have multiple dungeon levels, we need to know how deep this map is.
	// might be used to spawning level appropriate creatures
	void setLevel(int l);
	// can things walk on this square
	bool isWalkable(int x, int y);
	// since some things use point, another way of asking about walkability
	bool isWalkable(Point *p);
	// return a trigger (or NULL) at a a given X and Y
	Trigger *getTriggerAt(int x, int y);
	// find the stairs down on this level - here so when the player moves to the level,
	// they are on the appropriate staircase
	StairsDown *getStairsDown();
	// find the stairs up on this level - here so when the player moves to the level,
	// they are on the appropriate staircase
	StairsUp *getStairsUp();
	// deal with a player command - for now, this is search, open and close,
	// with the x and y being the location the player is at when they did the
	// command
	void processCommand(PlayerCommands command, int x, int y);
	// remove a trigger from the model
	void removeTrigger(Trigger *t);
	// add a trigger to the model
	void addTrigger(Trigger *t);
	// process anything special that needs to happen when the player
	// visits a particular x and y
	void visit(int x, int y);
	// create creatures for this level
	virtual void spawnCreatures(); // virtual in case some levels want to do it differently
	// add a creature to this level.  Spawn will talk to the creature factory,
	// which will in turn call this method
	void addCreature(Creature *c);
	// return the creature (or NULL) at a given location
	Creature * getCreatureAt(int x, int y);
	// called when something dies.  Also cleans up the proxy
	void removeCreature(Creature *c);
protected:
	// these are protected so subclasses can access them directly.  Otherwise,
	// we'd need set methods as well, and we don't want the general code to be able
	// to fiddle with the models and views.

	MapModel *model; // subclasses will populate this
	MapView *view; // subclasses will populate this
	int level; // how deep in the dungeon is this map
};