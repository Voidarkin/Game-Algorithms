#pragma once
#include "Component.h"
// Component that modifies the target's armor class
// negative is better.
class ACModComponent :
	public Component
{
public:
	ACModComponent(int amount);
	virtual ~ACModComponent();

	// Inherited via Component
	virtual bool isType(ComponentType type) override;
	// accessor
	int getACModification();
private:
	// how much the armor changes. -2 would be leather, -5 chain, -8 plate etc.
	int acModification;
};