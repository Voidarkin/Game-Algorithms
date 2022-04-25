#include "stdafx.h"
#include "MoveCommand.h"
#include "Creature.h"

MoveCommand::MoveCommand()
{
}


MoveCommand::~MoveCommand()
{
}

void MoveCommand::execute()
{
	creature->move(dx, dy);
}

void MoveCommand::setDirection(int theDX, int theDY)
{
	dx = theDX;
	dy = theDY;
}
