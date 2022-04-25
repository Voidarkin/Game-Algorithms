#include "stdafx.h"
#include "Armor.h"
#include <sstream>
#include "Dungeon.h"
// base class for all armor
Armor::Armor()
{
}

Armor::~Armor()
{
}

// subclasses will add to this
std::string Armor::getDescription()
{
	return "";
}

Entity * Armor::getSubComponents()
{
	Entity * sub = new Entity(ComponentType::ARMOR);
	return sub;
}