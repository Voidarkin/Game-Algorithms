#pragma once
#include "Item.h"
#include <string>
#include <vector>
#include "Entity.h"
// Armor is a specific type of item.  Where it goes depends on the type of subcomponents it has
class Armor :
	public Item
{
public:
	Armor();
	virtual ~Armor();
	// what are we
	virtual std::string getDescription();
	virtual Entity *getSubComponents();
};