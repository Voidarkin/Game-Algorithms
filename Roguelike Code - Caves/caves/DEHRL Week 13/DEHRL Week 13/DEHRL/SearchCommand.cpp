#include "stdafx.h"
#include "SearchCommand.h"
#include "Dungeon.h"

SearchCommand::SearchCommand()
{
}


SearchCommand::~SearchCommand()
{
}

void SearchCommand::execute()
{
	Dungeon::getInstance()->getCurrentMap()->processCommand(PlayerCommands::SEARCH, x, y);

}
