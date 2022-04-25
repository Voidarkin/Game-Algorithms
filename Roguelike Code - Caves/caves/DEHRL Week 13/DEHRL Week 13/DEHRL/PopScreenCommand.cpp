#include "stdafx.h"
#include "PopScreenCommand.h"
#include "ScreenManager.h"
// request that the screen manager pops a screen off it's stack
PopScreenCommand::PopScreenCommand()
{
}

PopScreenCommand::~PopScreenCommand()
{
}

// little red button
void PopScreenCommand::execute()
{
	ScreenManager::getInstance()->popScreen();
}