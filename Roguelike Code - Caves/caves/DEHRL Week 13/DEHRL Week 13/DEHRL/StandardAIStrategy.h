#pragma once
#include "AIStrategy.h"
#include "Creature.h"
class StandardAIStrategy :
	public AIStrategy
{
public:
	StandardAIStrategy();
	~StandardAIStrategy();

	// Inherited via AIStrategy
	virtual void dealWithPlayer() override;

	// Inherited via AIStrategy
	virtual int getTargetX() override;
	virtual int getTargetY() override;
	virtual void setCreature(Creature *c);
private:
	int prevX;
	int prevY;
	int timestanding;
};

