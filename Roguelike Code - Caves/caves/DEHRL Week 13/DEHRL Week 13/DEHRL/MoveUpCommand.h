#pragma once
#include "DungeonCommand.h"
class MoveUpCommand :
	public DungeonCommand
{
public:
	MoveUpCommand();
	~MoveUpCommand();

	// Inherited via DungeonCommand
	virtual void execute() override;
};

