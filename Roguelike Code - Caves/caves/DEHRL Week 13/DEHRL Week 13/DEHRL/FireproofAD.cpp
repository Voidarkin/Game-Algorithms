#include "stdafx.h"
#include "FireproofAD.h"

// add fireproofing to armor. reduces fire damage by 50%, but increases ice damage by 25%
FireproofAD::FireproofAD(Armor *a):ArmorDecorator(a)
{
}

FireproofAD::~FireproofAD()
{
}

// add fireproof in front of thing we're wrapped around
std::string FireproofAD::getDescription()
{
	return "Fireproof " + armor->getDescription();
}

Entity * FireproofAD::getSubComponents()
{
	// can go anywhere armor is
	Entity * sub = new Entity(ComponentType::ARMOR);
	ProtectionComponent *pc = new ProtectionComponent(DamageType::FIRE, 0.5);
	sub->addComponent(pc);
	// extra damage from ICE
	pc = new ProtectionComponent(DamageType::ICE, -0.25);
	sub->addComponent(pc);
	sub->addComponent(armor->getSubComponents());
	return sub;
}