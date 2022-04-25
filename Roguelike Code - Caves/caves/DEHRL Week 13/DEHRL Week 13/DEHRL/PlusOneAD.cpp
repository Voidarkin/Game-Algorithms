#include "stdafx.h"
#include "PlusOneAD.h"

// plus one armor
PlusOneAD::PlusOneAD(Armor *a):ArmorDecorator(a)
{
}

PlusOneAD::~PlusOneAD()
{
}

// +1 whatever
std::string PlusOneAD::getDescription()
{
	return "+1 " + armor->getDescription();
}

Entity * PlusOneAD::getSubComponents()
{
	// can go anywhere armor is
	Entity * sub = new Entity(ComponentType::ARMOR);
	// makes it harder to hit you
	ACModComponent *prot = new ACModComponent(-1);
	sub->addComponent(prot);
	sub->addComponent(armor->getSubComponents());
	return sub;
}