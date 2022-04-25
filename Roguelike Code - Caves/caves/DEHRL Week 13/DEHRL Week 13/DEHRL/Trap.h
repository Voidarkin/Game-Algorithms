#pragma once
#include "Trigger.h"
// thing that makes you go ouch
class Trap :
	public Trigger
{
public:
	Trap();
	virtual ~Trap();

	// Inherited via Trigger
	virtual void render() override;
	virtual void fireTrigger(Creature * c) override;
	virtual TriggerTypes getTriggerType() override;
	virtual bool isWalkable(int x, int y) override;
	virtual void applyPlayerAction(PlayerCommands command, int x, int y);
protected:
	void searchForTrap(int theX, int theY);
	// if we found a door, queue for deletion, and add a door in our place
	void foundTrap();
	void tryToDisarmTrap(int theX, int theY);
	// if we found a door, queue for deletion, and add a door in our place
	void disarmTrap();
	bool hasSeen;
};