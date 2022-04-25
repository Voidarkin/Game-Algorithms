#pragma once
#include "Command.h"
class Creature;

class CreatureCommand :
	public Command
{
public:
	CreatureCommand();
	virtual ~CreatureCommand();
	void setCreature(Creature *c);
protected:
	Creature *creature;
};