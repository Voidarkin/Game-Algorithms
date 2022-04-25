#pragma once
#include "EnemyState.h"
class Creature;
// creature observer is notified if a particualr creature changes it's position.  some things want
// the creature itself, others want the new positon.
class CreatureObserver
{
public:
	CreatureObserver();
	virtual ~CreatureObserver();
	// overridden in subclasses to process a movement of acreature.
	virtual void notify(Creature *c, EnemyState *state) = 0;
};