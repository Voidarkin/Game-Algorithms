#pragma once
#include "WeaponDecorator.h"
// weight on the end of a stick.  d6 damage
class Mace :
	public WeaponDecorator
{
public:
	Mace(Weapon *w);
	virtual ~Mace();
	// "Mace"
	virtual std::string getDescription();
	virtual Entity *getSubComponents();
};