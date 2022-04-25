#include "stdafx.h"
#include "Map.h"

// base implementation of the map.  Mostly empty
Map::Map()
{
}


Map::~Map()
{
}

// accessor method
MapModel * Map::getModel()
{
	return model;
}

// accessor method
MapView * Map::getView()
{
	return view;
}

// let the particular map model sort out how to find a space that is not a wall.
// that code wil be radically different when we look at different ways to dig
// dungeons. 
Point * Map::getRandomEmptySpace()
{
	return model->getRandomEmptySpace();
}

// set how deep th emap is
void Map::setLevel(int l)
{
	level = l;
}

// can we walk on this grid location?
bool Map::isWalkable(int x, int y)
{
	return model->isWalkable(x, y);
}

// can we walk on this grid location?
bool Map::isWalkable(Point * p)
{
	return isWalkable(p->getX(), p->getY());
}

// what trigger (if any) is at x,y
Trigger * Map::getTriggerAt(int x, int y)
{
	return model->getTriggerAt(x, y);
}

//Accessor 
StairsDown * Map::getStairsDown()
{
	return model->getStairsDown();;
}

//Accessor 
StairsUp * Map::getStairsUp()
{
	return model->getStairsUp();
}

// ask the model to deal with things the player wants to do
void Map::processCommand(PlayerCommands command, int x, int y)
{
	model->processCommand(command, x, y);
}

// ask the model to get rid of a trigger
void Map::removeTrigger(Trigger * t)
{
	model->removeTrigger(t);
}

// ask the model to add a trigger to it's list.
void Map::addTrigger(Trigger * t)
{
	model->addTrigger(t);
}

// inform the model that the player has been here
void Map::visit(int x, int y)
{
	model->visit(x, y);
}

// ask the model to spawn appropriate creatures
void Map::spawnCreatures()
{
	model->spawnCreatures(level);
}

// called by the creature factory, will find a spot for it, and put the creature there
void Map::addCreature(Creature * c)
{
	c->setPosition(getRandomEmptySpace());
	model->addCreature(c);
}

Creature * Map::getCreatureAt(int x, int y)
{
	return model->getCreatureAt(x, y);
}

void Map::removeCreature(Creature * c)
{
	model->removeCreature(c);
}