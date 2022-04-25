#include "stdafx.h"
#include "PlusOneWD.h"

// plus one weapon
PlusOneWD::PlusOneWD(Weapon *w) : WeaponDecorator(w)
{
}

PlusOneWD::~PlusOneWD()
{
}

// +1 whatever
std::string PlusOneWD::getDescription()
{
	return "+1 " + weapon->getDescription();
}

// +1 magic damage, and plus 1 to hit as well.
Entity * PlusOneWD::getSubComponents()
{
	Entity * sub = new Entity(ComponentType::WEAPON);
	DamageComponent *dam = new DamageComponent(DamageType::MAGIC, 1, 1);
	HitModComponent *hitMod = new HitModComponent(1);
	sub->addComponent(dam);
	sub->addComponent(hitMod);
	sub->addComponent(weapon->getSubComponents());
	return sub;
}