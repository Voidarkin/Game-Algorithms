#include "stdafx.h"
#include "StandardMapView.h"
#include "Room.h"
#include "Hallway.h"
#include "Corner.h"
#include "Trigger.h"
#include <vector>
#include "Creature.h"
#include "EnemyProxy.h"
// when we are handed a model, keep it
StandardMapView::StandardMapView(StandardMapModel *m)
{
	model = m;
}

StandardMapView::~StandardMapView()
{
}

// draw everything.  The pieces will determine on their own if they should be drawn or not
// it's not our repsonsibility.
void StandardMapView::render()
{
	// draw all the rooms
	std::vector<Room *> *rooms = model->getRooms();
	for each (Room *room in (*rooms))
	{
		room->render();
	}
	// draw all the hallways
	std::vector<Hallway *> *hallways = model->getHallways();
	for each (Hallway *hallway in (*hallways))
	{
		hallway->render();
	}
	// draw all the corners
	std::vector<Corner *> *corners = model->getCorners();
	for each (Corner *corner in (*corners))
	{
		corner->render();
	}
	// draw all the triggers
	std::vector<Trigger *> *triggers = model->getTriggers();
	for each (Trigger *trigger in (*triggers))
	{
		trigger->render();
	}
	// now, instead of drawing the creatures, we draw their proxies.
	std::vector<EnemyProxy *> *enemies = model->getEnemies();
	for each (EnemyProxy *enemy in (*enemies))
	{
		enemy->render();
	}
}