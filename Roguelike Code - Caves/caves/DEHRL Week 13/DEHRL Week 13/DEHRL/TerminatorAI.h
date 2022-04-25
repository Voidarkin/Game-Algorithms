#pragma once
#include "CreatureController.h"
#include "Model.h"
#include "Enemy.h"
class TerminatorAI :
	public CreatureController, public Model
{
public:
	TerminatorAI(Creature *c);
	~TerminatorAI();

	// Inherited via Model
	virtual void update(int milliseconds) override;
	void run();
};

