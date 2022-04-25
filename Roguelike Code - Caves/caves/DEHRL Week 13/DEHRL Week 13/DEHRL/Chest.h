#pragma once
#include "Trigger.h"
// a chest of gold. must be opened to access it
class Chest :
	public Trigger
{
public:
	Chest();
	virtual ~Chest();

	// Inherited via Trigger
	virtual void render() override;
	virtual void fireTrigger(Creature * c) override;
	virtual TriggerTypes getTriggerType() override;
	virtual bool isWalkable(int x, int y) override;

	virtual void applyPlayerAction(PlayerCommands command, int x, int y);
private:
	// called by applyPlayerAction to try to open the chest
	void attemptToOpen(int theX, int theY);
	// actually open the chest
	void openChest();
};