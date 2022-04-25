#include "stdafx.h"
#include "Trigger.h"
#include "DEHGE.h"
// trigger is anything that reacts when a creature moves onto it
Trigger::Trigger()
{
	position = NULL;
}

Trigger::~Trigger()
{
}

// most triggers just sit there
void Trigger::update(int milliseconds)
{
}

// accessor
void Trigger::setPosition(int theX, int theY)
{
	Point *p = new Point();
	p->setPosition(theX, theY);
	setPosition(p);
}

// accessor
void Trigger::setPosition(Point * p)
{
	if (position != NULL)
	{
		delete position;
	}
	position = p;
}

// accessor
int Trigger::getX()
{
	return position->getX();
}

//accessor
int Trigger::getY()
{
	return position->getY();
}

// placeholder in case subclasses don't need to respond to commands
void Trigger::applyPlayerAction(PlayerCommands command, int x, int y)
{
}

// show this trigger when rendering
void Trigger::makeVisible()
{
	visible = true;
}

// called when a creature moves. if it moved on top of us, fire the trigger
void Trigger::notify(Creature *c,EnemyState * state)
{
	if (getX() == state->getX() && getY() == state->getY())
	{
		fireTrigger(c);
	}
}