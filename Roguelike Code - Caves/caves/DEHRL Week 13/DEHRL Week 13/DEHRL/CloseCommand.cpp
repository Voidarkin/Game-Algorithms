#include "stdafx.h"
#include "CloseCommand.h"
#include "Dungeon.h"

CloseCommand::CloseCommand()
{
}


CloseCommand::~CloseCommand()
{
}

void CloseCommand::execute()
{
	Dungeon::getInstance()->getCurrentMap()->processCommand(PlayerCommands::CLOSE, x,y);
}
