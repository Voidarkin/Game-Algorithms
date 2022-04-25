#include "stdafx.h"
#include "QuitCommand.h"
#include "DEHGE.h"
// Request that we shutdown
QuitCommand::QuitCommand()
{
}

QuitCommand::~QuitCommand()
{
}

// the little red button
void QuitCommand::execute()
{
	DEHGE::getInstance()->requestShutDown();
}