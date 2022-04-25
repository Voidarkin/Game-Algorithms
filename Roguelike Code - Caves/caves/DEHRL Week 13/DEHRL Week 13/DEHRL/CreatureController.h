#pragma once
#include "CreatureCommandMessageQueue.h"
#include "Creature.h"
class CreatureController
{
public:
	CreatureController(Creature *c);
	virtual ~CreatureController();
	CreatureCommandMessageQueue *getQueue();
protected:
	CreatureCommandMessageQueue *queue;
	Creature *creature;
};

