#include "stdafx.h"
#include "Chainmail.h"

// armor made of small interlocked rings - gives 5 points to ac
Chainmail::Chainmail(Armor *a): ArmorDecorator(a)
{
}

Chainmail::~Chainmail()
{
}

std::string Chainmail::getDescription()
{
	return "Chain Mail" + armor->getDescription();
}

Entity * Chainmail::getSubComponents()
{
	Entity * sub = new Entity(ComponentType::BODY_ARMOR);
	// does not reduce damage at all, and gives -5 ac
	ACModComponent *prot = new ACModComponent(-5);
	sub->addComponent(prot);
	sub->addComponent(armor->getSubComponents());
	return sub;
}