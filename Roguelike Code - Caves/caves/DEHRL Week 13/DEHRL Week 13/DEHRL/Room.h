#pragma once
#include "Model.h"
#include "View.h"
#include "Point.h"
#include "CreatureObserver.h"
#include "Trigger.h"
#include <vector>
// class for a single room in a dungeon
// is both a model and a view - it stores data, and can draw itself
class Room :
	public Model, public View, public CreatureObserver
{
public:
	Room();
	// alternate constructor - with all parameters set at once.
	Room(int theX, int theY, int theWidth, int theHeight, bool visited = false);
	virtual ~Room();
	// draw the room on the screen
	void render();
	// process any changes to the room
	void update(int milliseconds);
	// accessors to the location and size of the room
	void setX(int theX);
	void setY(int theY);
	void setWidth(int theWidth);
	void setHeight(int theHeight);
	// accessor to indicate if the player has been in this room before
	// used by render to determine if the room should be drawn or not
	void setVisited(bool visited);
	// accessors
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	// has this room been seen yet
	bool wasVisited();
	// find a spot inside the room
	Point * getRandomInterior();
	// does the room think we can stand here
	bool isWalkable(int x, int y);
	// player is now at x,y - does the room need to count as visited now?
	void visit(int x, int y);
	// is the point inside the room boundries (including walls)
	bool inside(int theX, int theY);
	// Inherited via CreatureObserver
	virtual void notify(Creature * c, EnemyState * state) override;
	// add and remove triggers from the room
	void addTrigger(Trigger *t);
	void removeTrigger(Trigger *t);
	// add and remove creatures from the room
	void addCreature(Creature *c);
	void removeCreature(Creature *c);
private:
	int x; // absolute room location
	int y;
	int width; // dimensions - including the wall
	int height;
	// have we been here already?
	bool hasBeenVisited;
	// things that go boom
	std::vector<Trigger *> triggers;
};