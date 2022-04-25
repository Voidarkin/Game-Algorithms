#pragma once
#include "Trigger.h"
// Like stairs Down, this allows the player to move up one dungeon level
class StairsUp :
	public Trigger
{
public:
	StairsUp();
	virtual ~StairsUp();

	// Inherited via Trigger
	// stairs up is a <
	virtual void render() override;
	// what happens when something steps on here?
	// eventually some creatures will head up the stairs to the previous level
	virtual void fireTrigger(Creature * c) override;
	// I am stairs up
	virtual TriggerTypes getTriggerType() override;
	// and you can walk on me.
	virtual bool isWalkable(int x, int y) override;
};