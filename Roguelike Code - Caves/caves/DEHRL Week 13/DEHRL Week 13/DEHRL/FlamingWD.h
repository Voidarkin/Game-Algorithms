#pragma once
#include "WeaponDecorator.h"
// add a d8 fire damage
class FlamingWD :
	public WeaponDecorator
{
public:
	// what weapon is on fire
	FlamingWD(Weapon *w);
	virtual ~FlamingWD();
	// "Flaming"
	virtual std::string getDescription();
	virtual Entity *getSubComponents();
};