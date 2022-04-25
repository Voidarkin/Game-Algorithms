#pragma once
#include "Armor.h"
#include "ProtectionComponent.h"
#include "ACModComponent.h"
// an armor dectorator is treated as armor, which it does by being bolted around existing armor
// this can (and does) include the base type of armor
class ArmorDecorator :
	public Armor
{
public:
	ArmorDecorator(Armor *a);
	virtual ~ArmorDecorator();
	// what is the combined description of this item (and the armor it is decorating)
	virtual std::string getDescription();
	virtual Entity *getSubComponents() = 0;
protected:
	// what are we decorating. since we're also a subclass of armor, you can layer decorations
	Armor *armor;
};