#include "stdafx.h"
#include "OneRoomMap.h"
#include "StandardMapModel.h"
#include "StandardMapView.h"
#include "Room.h"
#include "StairsDown.h"
#include "StairsUp.h"
#include "Door.h"
#include "Gold.h"
#include "Trap.h"
#include "Trapdoor.h"
#include "Chest.h"
// one room map uses the standard map model and view.  (rooms, hallways, corners)


// it has a single room that is 10x10 and some stairs down...
OneRoomMap::OneRoomMap()
{
	// set up the model
	StandardMapModel *m = new StandardMapModel();
	model = m; 
	// and the view
	StandardMapView *v = new StandardMapView(m);
	view = v;
	// add a room to the model
	// room is 10,10, will be set to visited (so it is drawn), and located
	// such that it's top left corner is at 10,10 in world coordinates
	Room *room = new Room(10, 10, 10, 10, false);
	// we have to use m, instead of model here.  The standard map model knows
	// about rooms, but the generic one doesn't.
	// m is of type StandardMapModel*, while model is of type MapModel*
	m->addRoom(room);
	// and add the stairs  down to the next level
	StairsDown *down = new StairsDown();
	down->setPosition(getRandomEmptySpace());
	m->addStairsDown(down);
	// and up to the previoous level
	StairsUp *up = new StairsUp();
	up->setPosition(getRandomEmptySpace());
	m->addStairsUp(up);
	Gold *g = new Gold(100);
	g->setPosition(getRandomEmptySpace());
	m->addTrigger(g);
	Trap *t = new Trap();
	t->setPosition(getRandomEmptySpace());
	m->addTrigger(t);
	for (int i = 0; i < 3; i++)
	{
		Chest *c = new Chest();
		c->setPosition(getRandomEmptySpace());
		m->addTrigger(c);
	}
	m->update(0); // move all the triggers to the active trigger list
}

OneRoomMap::~OneRoomMap()
{
}

void OneRoomMap::spawnCreatures()
{
}