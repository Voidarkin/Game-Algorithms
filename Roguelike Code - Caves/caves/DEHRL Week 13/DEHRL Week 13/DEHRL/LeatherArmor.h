#pragma once
#include "ArmorDecorator.h"
// slightly better than being naked (reduces ac by 2)
class LeatherArmor :
	public ArmorDecorator
{
public:
	LeatherArmor(Armor *a);
	virtual ~LeatherArmor();
	// "Leather armor"
	virtual std::string getDescription();
	virtual Entity *getSubComponents();
};