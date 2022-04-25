#pragma once
#include "Command.h"
class DungeonCommand :
	public Command
{
public:
	DungeonCommand();
	~DungeonCommand();
	void init(int theX, int theY);
protected:
	int x;
	int y;
};

