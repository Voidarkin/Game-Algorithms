#include "stdafx.h"
#include "Mace.h"

// 1d6 damage piece of wood with a weight at one end
Mace::Mace(Weapon *w) :WeaponDecorator(w)
{
}

Mace::~Mace()
{
}

std::string Mace::getDescription()
{
	return "Mace" + weapon->getDescription();
}

Entity * Mace::getSubComponents()
{
	Entity * sub = new Entity(ComponentType::WEAPON);
	DamageComponent *dam = new DamageComponent(DamageType::BLUNT, 1, 6);
	sub->addComponent(dam);
	sub->addComponent(weapon->getSubComponents());
	return sub;
}