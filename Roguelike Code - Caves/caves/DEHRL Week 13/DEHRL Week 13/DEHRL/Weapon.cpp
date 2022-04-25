#include "stdafx.h"
#include "Weapon.h"
#include <sstream>
#include "Dungeon.h"

// base weapon class - everything that hurts starts here
Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

std::string Weapon::getDescription()
{
	return "";
}

Entity * Weapon::getSubComponents()
{
	Entity * sub = new Entity(ComponentType::WEAPON);
	return sub;
}