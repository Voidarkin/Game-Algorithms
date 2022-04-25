#pragma once
#include "MoveCommand.h"
class RunCommand :
	public MoveCommand
{
public:
	RunCommand();
	~RunCommand();

	// Inherited via CreatureCommand
	virtual void execute() override;
	bool somethingInteresting(int ix, int iy);
};

