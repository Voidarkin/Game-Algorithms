#pragma once
#include "Component.h"
// tracks how much damage reduction (of a specific type) should take place.
// the damage factors for all protection of that type are added together, then
// incoming damage is modified base on that amount.
// vulnerabilities should be entered as negative numbers
// factor of 0.9 means 90% damage reduction.
// factor of -0.25 means you take 125% of damage of that type.
// damage type of ANY will be applied at the end of damage mitigation, and impacts total damage

class ProtectionComponent :
	public Component
{
public:
	ProtectionComponent(DamageType type, float factor);
	virtual ~ProtectionComponent();

	// Inherited via Component
	virtual bool isType(ComponentType type) override;
	DamageType getProtectionType();
	float getProtectionFactor();
private:
	DamageType protectionType;
	float protectionfactor;
};