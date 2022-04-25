#pragma once
#include "CreatureCommand.h"
class MoveCommand :
	public CreatureCommand
{
public:
	MoveCommand();
	~MoveCommand();

	// Inherited via CreatureCommand
	virtual void execute() override;
	void setDirection(int theDX, int theDY);

protected:
	int dx;
	int dy;
};

