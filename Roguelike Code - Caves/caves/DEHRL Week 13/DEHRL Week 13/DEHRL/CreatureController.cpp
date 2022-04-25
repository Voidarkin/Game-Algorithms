#include "stdafx.h"
#include "CreatureController.h"


CreatureController::CreatureController(Creature *c)
{
	queue = new CreatureCommandMessageQueue();
	creature = c;
	c->setQueue(queue);
}


CreatureController::~CreatureController()
{
}

CreatureCommandMessageQueue * CreatureController::getQueue()
{
	return queue;
}
