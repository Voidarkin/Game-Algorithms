#pragma once
#include "DungeonCommand.h"
class MoveDownCommand :
	public DungeonCommand
{
public:
	MoveDownCommand();
	~MoveDownCommand();

	// Inherited via DungeonCommand
	virtual void execute() override;
};

