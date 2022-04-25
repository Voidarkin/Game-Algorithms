#pragma once
#include "MapModel.h"
#include "Corner.h"
#include "Hallway.h"
#include "Room.h"
#include <vector>
// the standard map model contains rooms, hallways and corners
class StandardMapModel :
	public MapModel
{
public:
	StandardMapModel();
	virtual ~StandardMapModel();
	// pick a random feature, and get an interior square for it.
	// note - this is not working at present.
	Point *getRandomEmptySpace();
	// accessor
	std::vector<Room *> *getRooms();
	// accessor
	std::vector<Hallway *> *getHallways();
	// accessor
	std::vector<Corner *> *getCorners();
	// add a room to the model. will eventually need addCorner
	void addRoom(Room *r);
	// add a hallway to the model
	void addHallway(Hallway *h);
	// deal with activating roms and hallways as the player moves
	void visit(int x, int y);
	// add and remove triggers from the map model
	void addTrigger(Trigger *t) override;
	void removeTrigger(Trigger *t) override;
	// add and remove creatures from the map model
	void addCreature(Creature *c) override;
	void removeCreature(Creature *c) override;
private:
	// data storage for the model.
	std::vector<Room *> *rooms;
	std::vector<Hallway *> *hallways;
	std::vector<Corner *> *corners;

	// Inherited via MapModel
	virtual bool isWalkable(int x, int y);
};