#pragma once
#include "DungeonCommand.h"
class DisarmCommand :
	public DungeonCommand
{
public:
	DisarmCommand();
	~DisarmCommand();

	// Inherited via DungeonCommand
	virtual void execute() override;
};

