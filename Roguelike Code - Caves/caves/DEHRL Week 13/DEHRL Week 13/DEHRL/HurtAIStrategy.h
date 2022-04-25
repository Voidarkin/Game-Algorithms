#pragma once
#include "AIStrategy.h"
#include "Dungeon.h"
class HurtAIStrategy :
	public AIStrategy
{
public:
	HurtAIStrategy();
	~HurtAIStrategy();

	// Inherited via AIStrategy
	virtual void dealWithPlayer() override;

	// Inherited via AIStrategy
	virtual int getTargetX() override;
	virtual int getTargetY() override;
};

