#pragma once
#include "AIStrategy.h"
#include <vector>
#include "CaveMapModel.h"
#include "Point.h"
#include "Creature.h"
#include "Dungeon.h"
class PathAIStrategy :
	public AIStrategy
{
public:
	PathAIStrategy();
	~PathAIStrategy();

	// Inherited via AIStrategy
	virtual int getTargetX() override;
	virtual int getTargetY() override;
	virtual void dealWithPlayer() override;
	virtual void setCreature(Creature *c);
	std::vector<Point *> *points;
	int stepsTaken = 0;
};

