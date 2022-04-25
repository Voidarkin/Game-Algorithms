#pragma once
#include "WeaponDecorator.h"
// short pointy knife.  d4 piercing damage
class Dagger :
	public WeaponDecorator
{
public:
	Dagger(Weapon *w);
	virtual ~Dagger();
	// "Dagger"
	virtual std::string getDescription();
	virtual Entity *getSubComponents();
};