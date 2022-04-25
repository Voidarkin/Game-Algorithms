#pragma once
#include "View.h"
#include "Model.h"
#include "Creature.h"
#include "Constants.h"
#include "Point.h"
#include "CreatureObserver.h"

// base class for things that cause interesting things to happen when you step on them.
// most of the userfil stuff will happen in the pure virtuals by the subclasses
class Trigger :
	public View, public Model, public CreatureObserver
{
public:
	Trigger();
	virtual ~Trigger();

	// Inherited via View
	// need a subclass to decide what this looks like.
	// note - rendering is NOT restricted to just the x and y location - it can be bigger...
	virtual void render() =0;

	// Inherited via Model
	// in case the trigger needs to do something special
	// not a pure virtual, but rather an empty method, since most triggers won't care.
	virtual void update(int milliseconds);

	// accessors
	void setPosition(int theX, int theY);
	void setPosition(Point *p);
	int getX();
	int getY();
	// what does the trigger do when stepped on?
	virtual void fireTrigger(Creature *c) = 0;
	// what type of trigger is this?
	virtual TriggerTypes getTriggerType() = 0;
	// can it even be walked on?
	// this will be important for closed vs open doors, which will have additional state info.
	virtual bool isWalkable(int x, int y) = 0;
	// try to apply a player action to this trigger
	virtual void applyPlayerAction(PlayerCommands command, int x, int y);
	// can they seem me yet?
	void makeVisible();

	// Inherited via CreatureObserver
	virtual void notify(Creature *c,EnemyState * state) override;
protected:
	// where is the trigger
	Point *position;
	// can they see the trigger or not
	bool visible;
};