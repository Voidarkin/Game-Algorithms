#pragma once
#include <string>
#include "Entity.h"
#include <vector>
// base class for all items
class Item
{
public:
	Item();
	virtual ~Item();
	// used by inventory, which doesn't care if weapon or armor
	virtual std::string getDescription()=0;
	// get the root entity
	virtual Entity *getEntity();
	// get the sub pieces of this item - overridden by decorators to do specific things
	virtual Entity *getSubComponents() = 0;
	void setEquipped(bool equip);
	bool isEquipped();
private:
	Entity *entity;
	bool equipped;
};