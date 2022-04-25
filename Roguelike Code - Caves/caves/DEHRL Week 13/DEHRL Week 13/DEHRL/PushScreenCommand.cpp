#include "stdafx.h"
#include "PushScreenCommand.h"
#include "ScreenManager.h"
// request that the screen manager push a new screen onto the stack
PushScreenCommand::PushScreenCommand()
{
}

PushScreenCommand::~PushScreenCommand()
{
}

// the little red button
void PushScreenCommand::execute()
{
	ScreenManager::getInstance()->pushScreen(screenID);
}

// set the screen id that will be pushed when we run
void PushScreenCommand::setScreenID(ScreenID id)
{
	screenID = id;
}