#include "stdafx.h"
#include "TerminatorAI.h"
#include <Windows.h>
#include "Dungeon.h"
#include "MoveCommand.h"
TerminatorAI::TerminatorAI(Creature *c) :CreatureController(c)
{
}


TerminatorAI::~TerminatorAI()
{
}

void TerminatorAI::update(int milliseconds)
{
	// run old code
	//creature->update(milliseconds);

	// what should we do?
	// figure out where to move, and drop in a move command to the queue
	if (creature->isVisible())
	{
		AIStrategy *strat = creature->getStrategy();

		// Where is the player, relative to us? (calculate dx and dy)
		int px = Dungeon::getInstance()->getPlayer()->getX();
		int py = Dungeon::getInstance()->getPlayer()->getY();
		int dx = px - creature->getX();
		int dy = py - creature->getY();
		if (dx*dx + dy*dy == 1)
		{
			strat->dealWithPlayer();
		}
		int tx = strat->getTargetX();
		int ty = strat->getTargetY();
		dx = tx - creature->getX();
		dy = ty - creature->getY();

		if (dx != 0)
		{
			dx = dx / abs(dx);
		}
		if (dy != 0)
		{
			dy = dy / abs(dy);
		}
		MoveCommand *m = new MoveCommand();
		m->setCreature(creature);
		m->setDirection(dx, dy);
		queue->push(m);
	}
}

void TerminatorAI::run()
{
	Enemy *e = (Enemy*)creature;
	while (e->getHP() > 0)
	{
		if (e->isActive())
		{
			update(e->getFrameDelay());
		}
		Sleep(e->getFrameDelay());
	}
	//delete creature;
	delete this;
}
