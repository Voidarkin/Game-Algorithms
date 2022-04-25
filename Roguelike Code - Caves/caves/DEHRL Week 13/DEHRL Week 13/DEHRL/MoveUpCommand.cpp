#include "stdafx.h"
#include "MoveUpCommand.h"
#include "StairsUp.h"
#include "Player.h"
#include "Dungeon.h"


MoveUpCommand::MoveUpCommand()
{
}


MoveUpCommand::~MoveUpCommand()
{
}

void MoveUpCommand::execute()
{
	Point *p = Dungeon::getInstance()->getPlayer()->getPosition();
	StairsUp *su = Dungeon::getInstance()->getCurrentMap()->getStairsUp();
	if (su != NULL && su->getX() == p->getX() && su->getY() == p->getY())
	{
		Dungeon::getInstance()->moveUp();
	}
}
