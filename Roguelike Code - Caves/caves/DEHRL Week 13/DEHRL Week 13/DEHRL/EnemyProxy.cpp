#include "stdafx.h"
#include "EnemyProxy.h"
#include "EnemyStateMessageQueue.h"
#include "DEHRender.h"
// an Enemy proxy is a visible proxy for the indepoendent enemy.  it's here so we can be
// drawn in the main game loop
EnemyProxy::EnemyProxy(char c, int theX, int theY, EnemyStateMessageQueue *theQueue)
{
	// what do we draw
	displayChar = c;
	// where do we draw it
	x = theX;
	y = theY;
	// and how do we get updates about location
	queue = theQueue;
}

EnemyProxy::~EnemyProxy()
{
}

// render the last received state of the enemy
void EnemyProxy::render()
{
	DEHRender::getInstance()->drawChar(x, y, displayChar, true);
}

// pull the last known state from the queue.  (Remove all the previous one - we're not going to
// draw a trail of movement)
void EnemyProxy::update(int milliseconds)
{
	// pull info off the message queue, and update our position accordingly
	if (queue->empty() == true)
	{ 
		return;
	}
	EnemyState *state = queue->last();
	x = state->getX();
	y = state->getY();
}

int EnemyProxy::getX()
{
	return x;
}

int EnemyProxy::getY()
{
	return y;
}
