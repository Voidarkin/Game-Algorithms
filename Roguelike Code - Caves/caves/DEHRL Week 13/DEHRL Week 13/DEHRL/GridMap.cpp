#include "stdafx.h"
#include "GridMap.h"
#include "StandardMapModel.h"
#include "StandardMapView.h"
#include "Room.h"
#include "StairsDown.h"
#include "StairsUp.h"
#include "Door.h"
#include "SecretDoor.h"
#include "Gold.h"
#include "Trap.h"
#include "Trapdoor.h"
#include "Chest.h"
#include "LootItem.h"
#include "Item.h"
#include "ItemFactory.h"
// 3 x 3 grid of rooms, connected fully with hallways
// uses the standard map model and view
GridMap::GridMap(int l)
{
	setLevel(l);
	// set up the model
	StandardMapModel *m = new StandardMapModel();
	model = m;
	// and the view
	StandardMapView *v = new StandardMapView(m);
	view = v;
	// we have 9 rooms, and for now, 12 hallways
	Room *room1 = new Room(10, 10, 15, 10, false);
	m->addRoom(room1);
	Room *room2 = new Room(35, 10, 15, 10, false);
	m->addRoom(room2);
	Room *room3 = new Room(60, 10, 15, 10, false);
	m->addRoom(room3);
	Room *room4 = new Room(10, 30, 15, 10, false);
	m->addRoom(room4);
	Room *room5 = new Room(35, 30, 15, 10, false);
	m->addRoom(room5);
	Room *room6 = new Room(60, 30, 15, 10, false);
	m->addRoom(room6);
	Room *room7 = new Room(10, 50, 15, 10, false);
	m->addRoom(room7);
	Room *room8 = new Room(35, 50, 15, 10, false);
	m->addRoom(room8);
	Room *room9 = new Room(60, 50, 15, 10, false);
	m->addRoom(room9);
	// first, the horizontal legs - 6 of those
	Hallway *h1 = new Hallway(26, 15, 9, HallwayType::HORIZONTAL, false);
	m->addHallway(h1);
	Hallway *h2 = new Hallway(26, 35, 9, HallwayType::HORIZONTAL, false);
	m->addHallway(h2);
	Hallway *h3 = new Hallway(26, 55, 9, HallwayType::HORIZONTAL, false);
	m->addHallway(h3);
	Hallway *h4 = new Hallway(51, 15, 9, HallwayType::HORIZONTAL, false);
	m->addHallway(h4);
	Hallway *h5 = new Hallway(51, 35, 9, HallwayType::HORIZONTAL, false);
	m->addHallway(h5);
	Hallway *h6 = new Hallway(51, 55, 9, HallwayType::HORIZONTAL, false);
	m->addHallway(h6);
	// now the verticals, 6 of those.
	Hallway *h7 = new Hallway(17, 21, 9, HallwayType::VERTICAL, false);
	m->addHallway(h7);
	Hallway *h8 = new Hallway(42, 21, 9, HallwayType::VERTICAL, false);
	m->addHallway(h8);
	Hallway *h9 = new Hallway(67, 21, 9, HallwayType::VERTICAL, false);
	m->addHallway(h9);
	Hallway *h10 = new Hallway(17, 41, 9, HallwayType::VERTICAL, false);
	m->addHallway(h10);
	Hallway *h11 = new Hallway(42, 41, 9, HallwayType::VERTICAL, false);
	m->addHallway(h11);
	Hallway *h12 = new Hallway(67, 41, 9, HallwayType::VERTICAL, false);
	m->addHallway(h12);

	// and now a pile of doors
	Trigger *d = NULL; 
	//H Left
	d = spawnDoor();
	d->setPosition(25, 15);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(35, 15);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(25, 35);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(35, 35);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(25, 55);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(35, 55);
	addTrigger(d);
	//H right
	d = spawnDoor();
	d->setPosition(50, 15);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(60, 15);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(50, 35);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(60, 35);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(50, 55);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(60, 55);
	addTrigger(d);
	//V Top
	d = spawnDoor();
	d->setPosition(17, 20);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(42, 20);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(67, 20);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(17, 30);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(42, 30);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(67, 30);
	addTrigger(d);
	//V Bottom
	d = spawnDoor();
	d->setPosition(17, 40);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(42, 40);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(67, 40);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(17, 50);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(42, 50);
	addTrigger(d);
	d = spawnDoor();
	d->setPosition(67, 50);
	addTrigger(d);
	StairsDown *down = new StairsDown();
	down->setPosition(getRandomEmptySpace());
	m->addStairsDown(down);
	StairsUp *up = new StairsUp();
	up->setPosition(getRandomEmptySpace());
	m->addStairsUp(up);
	// add some extra stuff
	int num = rand() % 10;
	for (int i = 0; i < num; i++)
	{
		Gold *g = new Gold(rand() % 150);
		g->setPosition(getRandomEmptySpace());
		m->addTrigger(g);
	}
	if (num == 0)
	{
		Trapdoor *td = new Trapdoor();
		td->setPosition(getRandomEmptySpace());
		m->addTrigger(td);
	}
	num = rand() % 10;
	for (int i = 0; i < num; i++)
	{
		Trap *t = new Trap();
		t->setPosition(getRandomEmptySpace());
		m->addTrigger(t);
	}
	num = rand() % 3;
	for (int i = 0; i < num; i++)
	{
		Chest *c = new Chest();
		c->setPosition(getRandomEmptySpace());
		m->addTrigger(c);
	}
	num = rand() % 3;
	for (int i = 0; i < num; i++)
	{
		Item *item = ItemFactory::getInstance()->generateItem(l);
		LootItem *li = new LootItem(item);
		li->setPosition(getRandomEmptySpace());
		m->addTrigger(li);
	}
	m->update(0);
}

GridMap::~GridMap()
{
}

// create doors (or secret doors) - more likely to get a secret door the deeper you go.
Trigger * GridMap::spawnDoor()
{
	int r = rand() % 50;
	if (r >= level)
	{
		return new Door();
	}
	else
	{
		return new SecretDoor();
	}
}