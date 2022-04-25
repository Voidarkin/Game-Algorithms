#include "stdafx.h"
#include "Platemail.h"

// basically a better tin can.  gives 8 points of armor protection
Platemail::Platemail(Armor *a): ArmorDecorator(a)
{
}

Platemail::~Platemail()
{
}

std::string Platemail::getDescription()
{
	return "Plate Mail" + armor->getDescription();
}

Entity * Platemail::getSubComponents()
{
	Entity * sub = new Entity(ComponentType::BODY_ARMOR);
	// does not reduce damage at all, and gives -8 ac
	ACModComponent *prot = new ACModComponent(-8);
	sub->addComponent(prot);
	sub->addComponent(armor->getSubComponents());
	return sub;
}