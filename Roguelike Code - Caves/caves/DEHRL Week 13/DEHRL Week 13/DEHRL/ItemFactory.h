#pragma once
#include "Item.h"
// singleton that spawns level appropriate items
class ItemFactory
{
public:
	// get the instance
	static ItemFactory* getInstance();
	// and make an item for level whatever
	Item *generateItem(int level);
private:
	ItemFactory();
	virtual ~ItemFactory();
	static ItemFactory *instance;
	// called by generate item
	Item *generateArmor(int level);
	// called by generate item
	Item *generateWeapon(int level);
};