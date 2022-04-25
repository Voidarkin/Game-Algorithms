#pragma once
#include "CreatureController.h"
#include "KeyController.h"
#include "Creature.h"
class PlayerController :
	public CreatureController, public KeyController
{
public:
	PlayerController(Creature *p);
	~PlayerController();

	// Inherited via KeyController
	virtual void keyPress(int key) override;
};

