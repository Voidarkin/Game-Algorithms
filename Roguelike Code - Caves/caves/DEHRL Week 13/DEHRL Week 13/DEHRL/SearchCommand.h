#pragma once
#include "DungeonCommand.h"
class SearchCommand :
	public DungeonCommand
{
public:
	SearchCommand();
	~SearchCommand();

	// Inherited via DungeonCommand
	virtual void execute() override;
};

