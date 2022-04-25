#pragma once
#include "Dungeon.h"
#include "Creature.h"
#include <vector>
#include <map>
#include <string>
// Creature factory does exactly what it sounds like
// it makes creatures that are appropriate for a particular level.
// different spawn methods will be added later to do thinbgs like clustering monsters.
// it's a singleton
class CreatureFactory
{
public:
	static CreatureFactory *getInstance();
	// spawn a monster (or set of related monsters) on a particular dungeon level
	void spawnMonster(int level);
private:
	CreatureFactory();
	~CreatureFactory();
	static CreatureFactory *instance;
	// the full names of each type of creature
	std::vector<std::string> names;
	// attributes has 26 entries.  each of those has a number of values
	// constants will be added when I have time to more easily map out those
	// attributes.  for now, read below.
	// 0 - Char on map
	// 1 - hit dice (0 == d4, everything else is number of d8's)
	// 2,3 - damage (#/dice)
	// 4 - armor class (old school D&D: 10 is helpless, lower numbers are harder
	// 5 - min level found on
	// 6 - max level found on
	// 7 - min number to spawn
	// 8 - max number to spawn
	// 9 - monster speed - what is the delay between updates for this enemy?
	// monster xp is 10 x their maximum hp, so will vary by monster.
	// xp also earned for picking up treasure - 1 xp per gp
	// 2,000 xp will level the player up
	std::vector<std::vector<int>> attributes;
};