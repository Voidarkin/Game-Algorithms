#pragma once
#include "Trigger.h"
// A secret door stays hidden, unless the use searches near it.
// then, ir will remove itself, and add a new Door object in it's place
// originally, had a bool to keep track of it's hidden status, then realized
// that it's mere existance was enough to say that it's hidden.
class SecretDoor :
	public Trigger
{
public:
	SecretDoor();
	virtual ~SecretDoor();

	// Inherited via Trigger
	virtual void render() override;
	// can thins step on closed secret doors?
	virtual void fireTrigger(Creature * c) override;
	// we're a secret door
	virtual TriggerTypes getTriggerType() override;
	// can they pass? No.
	virtual bool isWalkable(int x, int y) override;
	// only react to searh
	virtual void applyPlayerAction(PlayerCommands command, int x, int y);
	// try to search. will do nothing if the player is not nearby
	void searchForDoor(int theX, int theY);
	// if we found a door, queue for deletion, and add a door in our place
	void foundDoor();
};