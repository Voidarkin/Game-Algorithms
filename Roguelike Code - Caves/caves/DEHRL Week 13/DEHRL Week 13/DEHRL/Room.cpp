#include "stdafx.h"
#include "Room.h"
#include "DEHRender.h"
#include "Point.h"
#include "Trigger.h"
#include "Dungeon.h"
#include <vector>
#include "Creature.h"
// create an undefined room, with all values set to zero or false.
// will need to use the accessors to manually set everything
Room::Room()
{
}

// create a basic room with all parameters set
Room::Room(int theX, int theY, int theWidth, int theHeight, bool visited)
{
	x = theX;
	y = theY;
	width = theWidth;
	height = theHeight;
	hasBeenVisited = visited;
}

Room::~Room()
{
}

// a room is simply drawn as a filled in rectangle.  But only if we can see it.
void Room::render()
{
	if (hasBeenVisited)
	{
		DEHRender::getInstance()->fillRect(x, y, x + width, y + height, '#', '.', true);
	}
}

// not much to do in the room...
void Room::update(int milliseconds)
{
}

// accessor
void Room::setX(int theX)
{
	x = theX;
}

// accessor
void Room::setY(int theY)
{
	y = theY;
}

//accessor
void Room::setWidth(int theWidth)
{
	width = theWidth;
}

//accessor
void Room::setHeight(int theHeight)
{
	height = theHeight;
}

// setting the room to visited will activate the contents of the room
void Room::setVisited(bool visited)
{
	hasBeenVisited = visited;
	if (visited == true)
	{
		// now we need to check the triggers in here to see if they need to turn on too
		std::vector<Trigger *> *triggers = Dungeon::getInstance()->getCurrentMap()->getModel()->getTriggers();
		for each (Trigger *t in (*triggers))
		{

			int tx = t->getX();
			int ty = t->getY();
			if (inside(tx, ty))
			{
				t->makeVisible();
			}
		}
		// now we need to check the cretures in here to see if they need to turn on too
		std::vector<Creature *> *creatures = Dungeon::getInstance()->getCurrentMap()->getModel()->getCreatures();
		for each (Creature *c in (*creatures))
		{

			int cx = c->getX();
			int cy = c->getY();
			if (inside(cx, cy))
			{
				c->makeVisible();
			}
		}
	}
}

// accessor
int Room::getX()
{
	return x;
}

// accessor
int Room::getY()
{
	return y;
}

// accessor
int Room::getWidth()
{
	return width;
}

// accessor
int Room::getHeight()
{
	return height;
}

// accessor
bool Room::wasVisited()
{
	return hasBeenVisited;
}

// locate clear space inside the room
Point * Room::getRandomInterior()
{
	Point *p = new Point();
	p->setPosition(x + rand() % (width - 2) + 1, y + rand() % (height - 2) + 1);
	return p;
}

// does this room think the space is clear?
bool Room::isWalkable(int theX, int theY)
{
	if (theX < (x + 1) || theX >(x + width - 1) || theY < (y + 1) || theY >(y + height - 1))
	{
		return false;
	}
	return true;
}

// if we've not already been in this room, then if the given x and y is inside
// (inside includes the walls)
// we've now visited it - activate the triggers, make it visible, and unleash the
// creatures
void Room::visit(int theX, int theY)
{
	if (hasBeenVisited)
	{
		return;
	}
	if (inside(theX, theY))
	{
		setVisited(true);
	}
}

// returns true if the x and y is contained within the room - this includes the walls.
bool Room::inside(int theX, int theY)
{
	if (theX >= x && theX <= x + width && theY >= y && theY <= y + height)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// called by creature when a creature in a room moves
void Room::notify(Creature * c, EnemyState * state)
{
	// is the creature still in the room?
	if (inside(state->getX(), state->getY()))
	{
		// yes, so poke the triggers
		for each (Trigger *t in triggers)
		{
			t->notify(c, state);
		}
	}
	else
	{
		// no - stop telling me you moved
		c->removeObserver(this);
	}
}

// adda  trigger to the room
void Room::addTrigger(Trigger * t)
{
	triggers.push_back(t);
}

// remove a trigger from the room
void Room::removeTrigger(Trigger * t)
{
	auto it = std::find(triggers.begin(), triggers.end(), t);
	if (it != triggers.end())
	{
		triggers.erase(it);
	}
}

// when a creature is added, it means we want to get it's movement notifications
void Room::addCreature(Creature * c)
{
	c->addObserver(this);
}

// stop sending us movement notifications
void Room::removeCreature(Creature * c)
{
	c->removeObserver(this);
}