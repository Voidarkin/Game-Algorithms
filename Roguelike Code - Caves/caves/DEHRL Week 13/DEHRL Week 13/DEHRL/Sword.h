#pragma once
#include "WeaponDecorator.h"
// standard sword - does a d8 of edged damage
class Sword :
	public WeaponDecorator
{
public:
	Sword(Weapon *w);
	virtual ~Sword();
	// "Sword"
	virtual std::string getDescription();
	virtual Entity *getSubComponents();
};