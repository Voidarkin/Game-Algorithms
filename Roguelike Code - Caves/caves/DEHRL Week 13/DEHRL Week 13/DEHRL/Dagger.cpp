#include "stdafx.h"
#include "Dagger.h"

// small pointy weapon - does a d4 piercing damage
Dagger::Dagger(Weapon *w) :WeaponDecorator(w)
{
}

Dagger::~Dagger()
{
}

std::string Dagger::getDescription()
{
	return "Dagger" + weapon->getDescription();
}

Entity * Dagger::getSubComponents()
{
	Entity * sub = new Entity(ComponentType::WEAPON);
	DamageComponent *dam = new DamageComponent(DamageType::PIERCING, 1, 4);
	sub->addComponent(dam);
	sub->addComponent(weapon->getSubComponents());
	return sub;
}