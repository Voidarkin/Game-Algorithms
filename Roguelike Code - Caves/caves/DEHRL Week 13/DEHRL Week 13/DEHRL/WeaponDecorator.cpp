#include "stdafx.h"
#include "WeaponDecorator.h"

// base wrapper around a weapon
WeaponDecorator::WeaponDecorator(Weapon *w)
{
	weapon = w;
}

WeaponDecorator::~WeaponDecorator()
{
}

// generically, proxy off to the weapon we're wrapped around
std::string WeaponDecorator::getDescription()
{
	return weapon->getDescription();
}