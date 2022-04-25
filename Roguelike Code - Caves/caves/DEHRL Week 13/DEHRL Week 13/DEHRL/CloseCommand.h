#pragma once
#include "DungeonCommand.h"
class CloseCommand :
	public DungeonCommand
{
public:
	CloseCommand();
	~CloseCommand();
	// Inherited via DungeonCommand
	virtual void execute() override;
};