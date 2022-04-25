#include "stdafx.h"
#include "OpenCommand.h"
#include "Dungeon.h"


OpenCommand::OpenCommand()
{
}


OpenCommand::~OpenCommand()
{
}

void OpenCommand::execute()
{
	Dungeon::getInstance()->getCurrentMap()->processCommand(PlayerCommands::OPEN, x, y);
}
