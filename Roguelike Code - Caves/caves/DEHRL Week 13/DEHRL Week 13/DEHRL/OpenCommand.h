#pragma once
#include "DungeonCommand.h"
class OpenCommand :
	public DungeonCommand
{
public:
	OpenCommand();
	~OpenCommand();

	// Inherited via DungeonCommand
	virtual void execute() override;
};

