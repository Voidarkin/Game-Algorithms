#pragma once
#include "Item.h"
#include <vector>
#include <string>
#include "Entity.h"
#include "DamageComponent.h"
#include "HitModComponent.h"
// base class for all weapon items
class Weapon :
	public Item
{
public:
	Weapon();
	virtual ~Weapon();
	// what are we
	virtual std::string getDescription();
	virtual Entity *getSubComponents();
};