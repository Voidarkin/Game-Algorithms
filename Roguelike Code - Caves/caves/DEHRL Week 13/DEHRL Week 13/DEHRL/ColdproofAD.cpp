#include "stdafx.h"
#include "ColdproofAD.h"

// ice proofing
ColdproofAD::ColdproofAD(Armor *a) :ArmorDecorator(a)
{
}

ColdproofAD::~ColdproofAD()
{
}

std::string ColdproofAD::getDescription()
{
	return "Coldproof "+armor->getDescription();
}

// 50% reduction in ice damage, but a 25% increase in fire damage...
Entity * ColdproofAD::getSubComponents()
{
	// can go anywhere armor is
	Entity * sub = new Entity(ComponentType::ARMOR);
	ProtectionComponent *pc = new ProtectionComponent(DamageType::ICE, 0.5);
	sub->addComponent(pc);
	// extra damage from fire
	pc = new ProtectionComponent(DamageType::FIRE, -0.25);
	sub->addComponent(pc);
	sub->addComponent(armor->getSubComponents());
	return sub;
}