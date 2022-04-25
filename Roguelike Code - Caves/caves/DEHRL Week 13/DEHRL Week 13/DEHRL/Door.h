#pragma once
#include "Trigger.h"
// an openable (and closeable) Door
class Door :
	public Trigger
{
public:
	Door();
	virtual ~Door();

	// Inherited via Trigger
	// draw the door (+ closed, = open)
	virtual void render() override;
	// do we need to do something when steped on?
	virtual void fireTrigger(Creature * c) override;
	// we're a door
	virtual TriggerTypes getTriggerType() override;
	// player can only step here if we're open
	virtual bool isWalkable(int x, int y) override;
	// if the player calls open or close, near us, try.
	virtual void applyPlayerAction(PlayerCommands command, int x, int y);
	// called by applyPlayerAction to try to open a door
	void attemptToOpen(int theX, int theY);
	// called by applyPlayerAction to try to close a door
	void attemptToClose(int theX, int theY);
	// are we open right now?
	bool isOpen();
private:
	// open = true, closed = false
	bool open;
};