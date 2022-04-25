#pragma once
#include "Model.h"
#include "View.h"
#include "Constants.h"
#include "CreatureObserver.h"
#include "Trigger.h"
// Hallways are now functional.  They are either horizontal or vertical
// they will be hidden until they have been visited.
class Hallway :
	public Model, public View, public CreatureObserver
{
public:
	Hallway();
	Hallway(int theX, int theY, int length, HallwayType type, bool visited = false);
	virtual ~Hallway();
	// draw either a horizontal or vertical chunk of hallway
	void render();
	// used to update the hallway - placeholder for now
	void update(int milliseconds);
	// the player has been here (or not)
	void setVisited(bool visited);
	// has the player been here?
	bool wasVisited();
	// does this location having been visited mean that this hallway now
	// counts as visited?
	void visit(int x, int y);
	// does the hallway think we can stand here?
	bool isWalkable(int x, int y);
	bool inside(int theX, int theY);
	// Inherited via CreatureObserver
	virtual void notify(Creature *c, EnemyState * state) override;
	// add and remove triggers from the hallways
	void addTrigger(Trigger *t);
	void removeTrigger(Trigger *t);
	// add and remove creatures from the area the hallway watches
	void addCreature(Creature *c);
	void removeCreature(Creature *c);
private:
	// things that are in the hallway
	std::vector<Trigger *> triggers;
	HallwayType type; // horizontal or vertical
	bool hasBeenVisited; // have we been to this hallway before
	// one end of the hallway
	int x;
	int y;
	// how far either left to right or up to down does it extend
	int length;
};