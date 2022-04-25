#include "stdafx.h"
#include "Sword.h"
#include "DamageComponent.h"
// base sword - 1-8 edged damage
Sword::Sword(Weapon *w) : WeaponDecorator(w)
{
}

Sword::~Sword()
{
}

std::string Sword::getDescription()
{
	return "Sword" +weapon->getDescription();
}

Entity * Sword::getSubComponents()
{
	Entity * sub = new Entity(ComponentType::WEAPON);
	DamageComponent *dam = new DamageComponent(DamageType::EDGED,1,8);
	sub->addComponent(dam);
	sub->addComponent(weapon->getSubComponents());
	return sub;
}