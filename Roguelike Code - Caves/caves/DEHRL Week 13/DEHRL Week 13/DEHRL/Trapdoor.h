#pragma once
#include "Trap.h"
// a trap that makes you fall down
class Trapdoor :
	public Trap
{
public:
	Trapdoor();
	virtual ~Trapdoor();

	// Inherited via Trap
	virtual void fireTrigger(Creature * c) override;
	virtual TriggerTypes getTriggerType() override;
private:
	// how many levels does this ride take us (1-10)
	int howFar;
};