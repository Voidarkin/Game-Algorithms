#pragma once
#include "Map.h"
class Trigger;
// 3 by 3 grid of rooms and hallways
class GridMap :
	public Map
{
public:
	GridMap(int l);
	virtual ~GridMap();
	Trigger *spawnDoor();
};