#include "stdafx.h"
#include "DamageComponent.h"

// stores info about a potential damage dealing effect/item
DamageComponent::DamageComponent(DamageType type, int min, int max)
{
	damageType = type;
	minDamage = min;
	maxDamage = max;
}

DamageComponent::~DamageComponent()
{
}

bool DamageComponent::isType(ComponentType type)
{
	return type == ComponentType::DAMAGE;
}

// accessor
DamageType DamageComponent::getDamageType()
{
	return damageType;
}

// pick a number between the min and max damage
int DamageComponent::rollDamage()
{
	int range = (maxDamage - minDamage) + 1;
	int result = rand() % range + minDamage;
	return result;
}