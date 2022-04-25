#pragma once
#include "Weapon.h"
#include "Constants.h"
#include <vector>
#include <string>
#include "DamageComponent.h"
// base class for anything that makes a weapon special
class WeaponDecorator :
	public Weapon
{
public:
	// what weapon are we wrapped around
	WeaponDecorator(Weapon *w);
	virtual ~WeaponDecorator();
	// what are we
	virtual std::string getDescription();
	virtual Entity *getSubComponents() = 0;
protected:
	// what we are decorating
	Weapon *weapon;
};