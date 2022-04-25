#pragma once
#include "Map.h"
// concrete map type that has a single room.  This is used for our initial dungeon
// level.  Eventually, it will also have a staircase that it uses to get to the
// next dungeon level.
class OneRoomMap :
	public Map
{
public:
	OneRoomMap();
	virtual ~OneRoomMap();
	// override so we don't get a bazillion creatures on top of us at the start
	virtual void spawnCreatures();
};