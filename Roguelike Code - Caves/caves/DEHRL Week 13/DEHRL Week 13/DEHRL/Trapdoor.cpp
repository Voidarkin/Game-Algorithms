#include "stdafx.h"
#include "Trapdoor.h"
#include "DEHRender.h"
#include "Dungeon.h"
// drop the player 1-10 levels deeper into the dungeon
Trapdoor::Trapdoor()
{
	hasSeen = false;
	howFar = rand() % 10 + 1;
}

Trapdoor::~Trapdoor()
{
}

// wheeeeee.....
void Trapdoor::fireTrigger(Creature * c)
{
	if (c == Dungeon::getInstance()->getPlayer())
	{
		Dungeon::getInstance()->fallDown(howFar);
		Dungeon::getInstance()->getStatusBar()->setMessage("You fall through a trapdoor...");
	}
}

// hole in the ground
TriggerTypes Trapdoor::getTriggerType()
{
	return TriggerTypes::TRAPDOOR;
}