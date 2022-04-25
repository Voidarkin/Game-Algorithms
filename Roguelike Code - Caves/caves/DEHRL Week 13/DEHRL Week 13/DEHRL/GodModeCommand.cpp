#include "stdafx.h"
#include "GodModeCommand.h"
#include "Dungeon.h"

GodModeCommand::GodModeCommand()
{
}


GodModeCommand::~GodModeCommand()
{
}

void GodModeCommand::execute()
{
	Dungeon::getInstance()->toggleGodMode();
}
