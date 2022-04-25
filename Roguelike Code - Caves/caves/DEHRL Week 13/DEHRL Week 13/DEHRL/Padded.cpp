#include "stdafx.h"
#include "Padded.h"

// padding added to armor reduces all damage by 25%, blunt by 50%,
// but at the cust of being bulky, which makes it easier to hit you.
Padded::Padded(Armor *a) :ArmorDecorator(a)
{
}

Padded::~Padded()
{
}

std::string Padded::getDescription()
{
	return "Padded "+armor->getDescription();
}

Entity * Padded::getSubComponents()
{
	// can go anywhere armor is
	Entity * sub = new Entity(ComponentType::ARMOR);
	// makes it easier to hit you
	ACModComponent *prot = new ACModComponent(1);
	sub->addComponent(prot);
	ProtectionComponent *pc = new ProtectionComponent(DamageType::ANY, 0.25);
	sub->addComponent(pc);
	pc = new ProtectionComponent(DamageType::BLUNT, 0.25);
	sub->addComponent(pc);
	sub->addComponent(armor->getSubComponents());
	return sub;
}