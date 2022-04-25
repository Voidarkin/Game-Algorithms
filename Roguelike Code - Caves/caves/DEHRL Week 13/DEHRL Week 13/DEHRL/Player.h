#pragma once
#include "Model.h"
#include "View.h"
#include "Point.h"
#include "Creature.h"
#include <vector>
#include "Item.h"
// the player - it's a model, view and key controller (and eventually will be a
// mouse controller as well) However, it doesn't need to directly inherit from
// model and view - it gets those via creature
class Player :
	public Creature
{
public:
	Player();
	virtual ~Player();

	// model methods
	// for now this needs to update the accumulated millisecondsAlive variable
	void update(int milliseconds);

	// view methods
	// draw the player (an @ sign) at the position of the player on the map
	void render();
	// return the total milliseconds the player has been alive
	long getMillisecondsAlive();
	// hand out xp - may result in leveling up the player
	bool awardXP(int xp);
	// how many xp do we have - used by status bar
	int getXP();
	// move by delta x and delta y
	void move(int dx, int dy);
	void addGold(int amount);
	int getGold();
	CreatureType getCreatureType();
	// add an item to inventory
	void addItem(Item * item);
	// discard an item from inventory, destroying it
	void dropItem(Item *item);
	// accessor
	std::vector<Item *> *getInventory();
	// put the placeholders for equipment to be equipped into place
	void setupBaseEquipment();
	// equip and inventory item
	void equipItem(Item *item);
	// unequip an inventory item
	void unequipItem(Item *item);
	// equip armor
	void equipArmor(Item *item);
	// equip something in a hand (most likely a weapon, also works for shields)
	void equipWeapon(Item *item);
	// put something on your head
	void equipHelm(Item *item);
	// put soemthing on your body
	void equipBodyArmor(Item *item);
private:
	// helper - once we know where we're removing something from, this is used to get rid of it.
	bool unequipItem(Item *item, Entity *bodypart);
	// how long have they been on screen (used by the status bar)
	long millisecondsAlive = 0;
	// experience points.  2000 means a new level
	int exp;
	// are we resting now? if so, regain 1 hp every 3 seconds
	bool resting;
	// accumulate time spent resting to try to get to 3000
	int timeResting = 0;
	// cash on hand
	int gold;
	// items the player has picked up
	std::vector<Item *> *inventory;
	Entity *empty;
};