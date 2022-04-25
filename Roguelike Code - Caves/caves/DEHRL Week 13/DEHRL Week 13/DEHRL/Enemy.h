#pragma once
#include "Creature.h"
#include <string>
#include "EnemyStateMessageQueue.h"
#include "EnemyProxy.h"
// One class that runs most of the monsters (for now - Bat is a subclass...)
class Enemy :
	public Creature
{
public:
	Enemy();
	virtual ~Enemy();
	// try to move the monster - virtual so special subclasses can override this
	// NOTE this is called by a separate thread of execution, NOT by the main loop
	virtual void update(int milliseconds) override;
	// Inherited via View
	// draw the creature on the screen
	virtual void render() override;
	// activate a monster - when the player opens the door to their room...
	virtual void makeVisible();
	// what does this look like on the map
	void setChar(char c);
	// attempt to move towards x and y - this is NOT teleport
	void moveTo(int x, int y);
	// attempt to hit the player
	void move(int dx, int dy);
	void attackPlayer();
	// invoked by a separate thread
	void run();
	// allows adjustment of the thread timing
	void setFrameDelay(int f);
	// called when shifting floors - or potentially when pausing the game.
	int getFrameDelay();
	void pauseThread();
	// start everything moving again
	void resumeThread();
	bool isActive();
private:
	// how it looks on the map
	char displayCharacter;
protected:
	// main thread accessible proxy
	EnemyProxy *proxy;
	// how long do we sleep between updates
	int frameDelay;
	// the thread that is running the update
	std::thread *t;
	// are we actually doing anything right now?
	bool active;
	// Inherited via Creature
	virtual CreatureType getCreatureType() override;
};