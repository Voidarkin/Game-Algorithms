#pragma once
#include "Component.h"
// determines a min/max damage of a particular type.
// if you want a d6, you'd specify 1,6
// if you want 1, you'd specify 1,1
// if you want 2d6, put 2 of these each with 1,6
// if you want 2d6+2, out 2 with 1,6, and 1 with 2,2
class DamageComponent :
	public Component
{
public:
	DamageComponent(DamageType type, int min, int max);
	virtual ~DamageComponent();

	// Inherited via Component
	virtual bool isType(ComponentType type) override;
	// what type of damage
	DamageType getDamageType();
	// random number between min and max.
	int rollDamage();
private:
	DamageType damageType;
	int minDamage;
	int maxDamage;
};