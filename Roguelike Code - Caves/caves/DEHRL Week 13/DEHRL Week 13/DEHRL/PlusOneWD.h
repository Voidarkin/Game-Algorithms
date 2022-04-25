#pragma once
#include "WeaponDecorator.h"
#include "DamageComponent.h"
// +1 weapon - does more damage, and easier to hit
class PlusOneWD :
	public WeaponDecorator
{
public:
	PlusOneWD(Weapon *w);
	virtual ~PlusOneWD();
	// "+1"
	virtual std::string getDescription();
	virtual Entity *getSubComponents();
};