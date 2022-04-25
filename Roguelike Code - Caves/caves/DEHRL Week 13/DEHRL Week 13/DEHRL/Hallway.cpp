#include "stdafx.h"
#include "Hallway.h"
#include "DEHRender.h"
#include <vector>
#include "Trigger.h"
#include "Dungeon.h"
//Hallways now work - either horizontal or vertical
Hallway::Hallway()
{
}

// alternate constructor that takes everything we need for initialization
Hallway::Hallway(int theX, int theY, int l, HallwayType t, bool visited)
{
	x = theX;
	y = theY;
	length = l;
	type = t;
	hasBeenVisited = visited;
}

Hallway::~Hallway()
{
}

// draw either a horizontal or vertical hallway
void Hallway::render()
{
	// only draw if we've seen the hallway
	if (wasVisited())
	{
		switch (type)
		{
		case HallwayType::HORIZONTAL:
			// we need to extend the walls out by 1 so the doors (if any) at the end)
			// aren't floating in space
			DEHRender::getInstance()->drawHLine(x - 1, x + length, y - 1, '#', true);
			DEHRender::getInstance()->drawHLine(x, x + length-1, y, '.', true);
			DEHRender::getInstance()->drawHLine(x - 1, x + length, y + 1, '#', true);
			break;
		case HallwayType::VERTICAL:
			DEHRender::getInstance()->drawVLine(x - 1, y-1, y + length, '#', true);
			DEHRender::getInstance()->drawVLine(x, y, y + length - 1, '.', true);
			DEHRender::getInstance()->drawVLine(x + 1, y-1, y + length, '#', true);
			break;
		}
	}
}

// any updates required for the hallway.  This might make
// pieces of it visibile based on the player location
void Hallway::update(int milliseconds)
{
}

void Hallway::setVisited(bool visited)
{
	hasBeenVisited = visited;
	// show any triggers that are in the hallway
	// NOTE - SHOULD ALSO DO THE SAME FOR CREATURES IN THE HALLWAYS.
	// FOR NOW, SINCE CREATURES ONLY SPAWN IN ROOMS, WE'RE GOOD
	std::vector<Trigger *> *triggers = Dungeon::getInstance()->getCurrentMap()->getModel()->getTriggers();
	for each (Trigger *t in (*triggers))
	{

		int tx = t->getX();
		int ty = t->getY();
		if (type == HallwayType::HORIZONTAL)
		{
			// is this trigger in the walkable area of the hallway
			if (tx >= x - 1 && tx <= x + length && ty == y)
			{
				t->makeVisible();
			}
		}
		if (type == HallwayType::VERTICAL)
		{
			// is this trigger in the walkable area of the hallway
			if (tx == x && ty >= y - 1 && ty <= y + length)
			{
				t->makeVisible();
			}
		}
	}
}

// have we been here before
bool Hallway::wasVisited()
{
	return hasBeenVisited;
}

void Hallway::visit(int theX, int theY)
{
	if (hasBeenVisited)
	{
		return;
	}
	if (type == HallwayType::HORIZONTAL)
	{
		// if we step on the door at either end, we've been here
		if (theX >= x - 1 && theX <= x + length && theY >= y - 1 && theY <= y + 1)
		{
			setVisited(true);
		}
	}
	if (type == HallwayType::VERTICAL)
	{
		if (theX >= x - 1 && theX <= x + 1 && theY >= y - 1 && theY <= y + length)
		{
			setVisited(true);
		}
	}
}

// does the hallway think this is walkable?
// this is why we don't extend the hallway to include the door - otherwise we'd
// walk right through doors...
bool Hallway::isWalkable(int theX, int theY)
{
	switch (type)
	{
	case HallwayType::HORIZONTAL:
		if (y == theY && theX >= x && theX <= x + length - 1)
		{
			return true;
		}
		break;
	case HallwayType::VERTICAL:
		if (x == theX && theY >= y && theY <= y + length - 1)
		{
			return true;
		}
		break;
	}
	return false;
}

bool Hallway::inside(int theX, int theY)
{
	if (type == HallwayType::HORIZONTAL)
	{
		// if we step on the door at either end, we've been here
		if (theX >= x - 1 && theX <= x + length && theY >= y - 1 && theY <= y + 1)
		{
			return true;
		}
	}
	if (type == HallwayType::VERTICAL)
	{
		if (theX >= x - 1 && theX <= x + 1 && theY >= y - 1 && theY <= y + length)
		{
			return true;
		}
	}
	return false;
}

// called when a creature moved
void Hallway::notify(Creature *c, EnemyState * state)
{
	// is the creature still in the room?
	if (inside(state->getX(), state->getY()))
	{
		// yes, so poke all the triggers
		for each (Trigger *t in triggers)
		{
			t->notify(c, state);
		}
	}
	else
	{
		// no, so we no longer care about the creature.
		c->removeObserver(this);
	}
}

// adda  trigger to the room
void Hallway::addTrigger(Trigger * t)
{
	triggers.push_back(t);
}

// remove a trigger from the room
void Hallway::removeTrigger(Trigger * t)
{
	auto it = std::find(triggers.begin(), triggers.end(), t);
	if (it != triggers.end())
	{
		triggers.erase(it);
	}
}

// when a creature is added to the room, we want to be notified if it moves
void Hallway::addCreature(Creature * c)
{
	c->addObserver(this);
}

// if the creature is not in the room, stop telling us about it.
void Hallway::removeCreature(Creature * c)
{
	c->removeObserver(this);
}