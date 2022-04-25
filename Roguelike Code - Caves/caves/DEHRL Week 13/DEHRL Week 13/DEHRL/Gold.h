#pragma once
#include "Trigger.h"
// a pile of gold on the floor
class Gold :
	public Trigger
{
public:
	Gold(int gp);
	virtual ~Gold();

	// Inherited via Trigger
	virtual void render() override;
	virtual void fireTrigger(Creature * c) override;
	virtual TriggerTypes getTriggerType() override;
	virtual bool isWalkable(int x, int y) override;
private:
	// how much gold
	int amount;
};