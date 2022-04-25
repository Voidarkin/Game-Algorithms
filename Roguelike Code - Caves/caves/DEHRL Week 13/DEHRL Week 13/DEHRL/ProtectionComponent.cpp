#include "stdafx.h"
#include "ProtectionComponent.h"

// damage mitigation.  factors are assocaited with types.
// > 1 == immune to that damaage.
// 0-1 - takes partial damage
// < 0 - takes increased damage
ProtectionComponent::ProtectionComponent(DamageType type, float factor)
{
	protectionType = type;
	protectionfactor = factor;
}

ProtectionComponent::~ProtectionComponent()
{
}

bool ProtectionComponent::isType(ComponentType type)
{
	return type == ComponentType::PROTECTION;
}

DamageType ProtectionComponent::getProtectionType()
{
	return protectionType;
}

float ProtectionComponent::getProtectionFactor()
{
	return protectionfactor;
}