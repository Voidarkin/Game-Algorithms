#pragma once
#include "DungeonCommand.h"
class GodModeCommand :
	public DungeonCommand
{
public:
	GodModeCommand();
	~GodModeCommand();

	// Inherited via DungeonCommand
	virtual void execute() override;
};

