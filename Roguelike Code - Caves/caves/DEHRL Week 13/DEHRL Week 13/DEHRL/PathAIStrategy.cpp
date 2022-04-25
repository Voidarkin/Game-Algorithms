#include "stdafx.h"
#include "PathAIStrategy.h"


PathAIStrategy::PathAIStrategy()
{
	points = NULL;
}

PathAIStrategy::~PathAIStrategy()
{
}

int PathAIStrategy::getTargetX()
{
	// basically, we're going to use up the first value out of here
	if (points == NULL || points->size() == 0)
	{
		creature->setStrategy(creature->getDefaultStrategy());
		return creature->getX();
	}
	Point * p = points->at(0);
	return p->getX();
}

int PathAIStrategy::getTargetY()
{
	if (points == NULL || points->size() == 0)
	{
		return creature->getY();
	}
	Point * p = points->at(0);
	points->erase(points->begin());
	stepsTaken++;
	if (stepsTaken >= 15) // revert back to the old way of doing things if we've moved 15 steps along
		// the precomputed path.  This way, if they player is moving around a lot, the creatures won't
		// always only head to where he was... they will give uyp heading thedre, and go directly
		// after them again.
	{
		creature->setStrategy(creature->getDefaultStrategy());

		return p->getY();
	}
	return p->getY();
}

void PathAIStrategy::dealWithPlayer()
{
	creature->setStrategy(creature->getDefaultStrategy());
}

void PathAIStrategy::setCreature(Creature * c)
{
	AIStrategy::setCreature(c);
	Player *p = Dungeon::getInstance()->getPlayer();
	MapModel *model = Dungeon::getInstance()->getCurrentMap()->getModel();
	if (model->isCaveMapModel())
	{
		CaveMapModel * cm = (CaveMapModel *)model;
		points = cm->getPathPoints(p->getX(), p->getY(), c->getX(), c->getY());
	}
}
