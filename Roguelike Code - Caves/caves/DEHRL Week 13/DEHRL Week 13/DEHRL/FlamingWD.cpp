#include "stdafx.h"
#include "FlamingWD.h"

// add fire to a weapon (1-8 fire damage)
FlamingWD::FlamingWD(Weapon *w) : WeaponDecorator(w)
{
}

FlamingWD::~FlamingWD()
{
}

// add Flaming to the name
std::string FlamingWD::getDescription()
{
	return "Flaming " + weapon->getDescription();
}

Entity * FlamingWD::getSubComponents()
{
	Entity * sub = new Entity(ComponentType::WEAPON);
	DamageComponent *dam = new DamageComponent(DamageType::FIRE, 1, 8);
	sub->addComponent(dam);
	sub->addComponent(weapon->getSubComponents());
	return sub;
}