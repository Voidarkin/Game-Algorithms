#pragma once
#include "CreatureCommand.h"
class AttackCommand :
	public CreatureCommand
{
public:
	AttackCommand();
	~AttackCommand();

	// Inherited via CreatureCommand
	virtual void execute() override;
};

