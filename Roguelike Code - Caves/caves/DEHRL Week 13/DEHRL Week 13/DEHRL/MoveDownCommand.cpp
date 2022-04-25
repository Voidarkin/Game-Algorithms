#include "stdafx.h"
#include "MoveDownCommand.h"
#include "StairsDown.h"
#include "Player.h"
#include "Dungeon.h"

MoveDownCommand::MoveDownCommand()
{
}


MoveDownCommand::~MoveDownCommand()
{
}

void MoveDownCommand::execute()
{
	Point *p = Dungeon::getInstance()->getPlayer()->getPosition();
	StairsDown *su = Dungeon::getInstance()->getCurrentMap()->getStairsDown();
	if (su != NULL && su->getX() == p->getX() && su->getY() == p->getY())
	{
		Dungeon::getInstance()->moveDown();
	}
}