#include "stdafx.h"
#include "DisarmCommand.h"
#include "Dungeon.h"

DisarmCommand::DisarmCommand()
{
}


DisarmCommand::~DisarmCommand()
{
}

void DisarmCommand::execute()
{
	Dungeon::getInstance()->getCurrentMap()->processCommand(PlayerCommands::DISARM, x,y);
}