#include "stdafx.h"
#include "LeatherArmor.h"
#include "ProtectionComponent.h"
// leather armor (ac 8) is a decorator typically wrapped around basic armor
LeatherArmor::LeatherArmor(Armor *a) :ArmorDecorator(a)
{
}

LeatherArmor::~LeatherArmor()
{
}

std::string LeatherArmor::getDescription()
{
	return "Leather Armor" + armor->getDescription();
}

Entity * LeatherArmor::getSubComponents()
{
	Entity * sub = new Entity(ComponentType::BODY_ARMOR);
	// does not reduce damage at all, and gives -2 ac
	ACModComponent *prot = new ACModComponent(-2);
	sub->addComponent(prot);
	sub->addComponent(armor->getSubComponents());
	return sub;
}