#include "stdafx.h"
#include "HitModComponent.h"

// keeps track of things that make it easier or harder to hit
// note - ac could just have easily been done by suppling negative values here...
HitModComponent::HitModComponent(int amount)
{
	hitModification = amount;
}

HitModComponent::~HitModComponent()
{
}

bool HitModComponent::isType(ComponentType type)
{
	return type == ComponentType::HIT_MOD;
}

int HitModComponent::getHitModification()
{
	return hitModification;
}