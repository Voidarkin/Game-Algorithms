#include "stdafx.h"
#include "StandardMapModel.h"
#include "Dungeon.h"

StandardMapModel::StandardMapModel()
{
	// set up the storage space for the map.  Someone else will
	// fill them in - that depends on the actual map
	rooms = new std::vector<Room *>();
	hallways = new std::vector<Hallway *>();
	corners = new std::vector<Corner *>();
}

StandardMapModel::~StandardMapModel()
{
}

// find a spot that is not walls
Point * StandardMapModel::getRandomEmptySpace()
{
	// pick a random room from the lsit of rooms
	// then pick a random x and y inside that room
	int roomIndex = rand() % (rooms->size());
	Room *r = (*rooms)[roomIndex];
	return r->getRandomInterior();
}

//accessor
std::vector<Room*>* StandardMapModel::getRooms()
{
	return rooms;
}

//accessor
std::vector<Hallway*>* StandardMapModel::getHallways()
{
	return hallways;
}

//accessor
std::vector<Corner*>* StandardMapModel::getCorners()
{
	return corners;
}

//accessor
void StandardMapModel::addRoom(Room * r)
{
	rooms->push_back(r);
}

// accessor
void StandardMapModel::addHallway(Hallway * h)
{
	hallways->push_back(h);
}

// see if the given x and y is within any rooms or hallways
void StandardMapModel::visit(int x, int y)
{
	for each (Room *r in (*rooms))
	{
		r->visit(x, y); // binary or operater
	}
	for each (Hallway *h in (*hallways))
	{
		h->visit(x, y); // binary or operater
	}
}

// add a trigger does extra stuff if we are in a state where there are rooms.
void StandardMapModel::addTrigger(Trigger * t)
{
	MapModel::addTrigger(t);
	// add it to the rooms and hallways that contain it as well
	for each (Room *room in (*rooms))
	{
		if (room->inside(t->getX(), t->getY()))
		{
			room->addTrigger(t);
		}
	}
	for each (Hallway *hall in (*hallways))
	{
		if (hall->inside(t->getX(), t->getY()))
		{
			hall->addTrigger(t);
		}
	}
}

void StandardMapModel::removeTrigger(Trigger * t)
{
	MapModel::removeTrigger(t);
	// remove it from the rooms and hallways that contain it
	for each (Room *room in (*rooms))
	{
		if (room->inside(t->getX(), t->getY()))
		{
			room->removeTrigger(t);
		}
	}
	for each (Hallway *hall in (*hallways))
	{
		if (hall->inside(t->getX(), t->getY()))
		{
			hall->removeTrigger(t);
		}
	}
}

// adda  creature to the model, and then to each room and hallway
void StandardMapModel::addCreature(Creature * c)
{
	MapModel::addCreature(c);
	for each (Room *room in (*rooms))
	{
		if (room->inside(c->getX(), c->getY()))
		{
			room->addCreature(c);
		}
	}
	for each (Hallway *hall in (*hallways))
	{
		if (hall->inside(c->getX(), c->getY()))
		{
			hall->addCreature(c);
		}
	}
}

// remove from model, rooms and hallways
void StandardMapModel::removeCreature(Creature * c)
{

	for each (Room *room in (*rooms))
	{
		if (room->inside(c->getX(), c->getY()))
		{
			room->removeCreature(c);
		}
	}
	for each (Hallway *hall in (*hallways))
	{
		if (hall->inside(c->getX(), c->getY()))
		{
			hall->removeCreature(c);
		}
	}
	MapModel::removeCreature(c);
}

// merge together everythings opinions on can we walk here
bool StandardMapModel::isWalkable(int x, int y)
{
	bool result = false; // assume the worst
	// do the rooms think we can go there?
	for each (Room *r in (*rooms))
	{
		result = result | r->isWalkable(x, y); // binary or operater
	}
	// how about the hallways?
	for each (Hallway *h in (*hallways))
	{
		result = result | h->isWalkable(x, y); // binary or operater
	}
	// triggers? (i.e doors)
	for each (Trigger *t in (*triggers))
	{
		result = result | t->isWalkable(x, y);
	}
	// and is an orc sleeping in the way?
	for each (Creature *c in (*creatures))
	{
		if (c->getX() == x && c->getY() == y)
		{
			result = false; // creatures cannot be walked through
			break;
		}
	}
	// and things cannot walk on the player
	if (Dungeon::getInstance()->getPlayer()->getX() == x && Dungeon::getInstance()->getPlayer()->getY() == y)
	{
		result = false;
	}
	return result;
}