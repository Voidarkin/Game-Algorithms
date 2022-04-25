#pragma once
#include "Trigger.h"
// stairs down is a type of trigger that, when the player walks on it will eventually
// add a status bar message
// for now, it's here so we have soemthing to check against when the player trys to move down
class StairsDown :
	public Trigger
{
public:
	StairsDown();
	virtual ~StairsDown();

	// Inherited via Trigger
	// draws a >
	virtual void render() override;

	// Inherited via Trigger
	// executed when a creature moves on top of it
	virtual void fireTrigger(Creature * c);
	// returns STAIRS_DOWN - here so that things can make use of the type of trigger.
	virtual TriggerTypes getTriggerType();
	// can it currently be walked on
	// right now, returns true.  possible that you would have to find and kill all creatures
	// on a level to enable the stairs.
	bool isWalkable(int x, int y);
};