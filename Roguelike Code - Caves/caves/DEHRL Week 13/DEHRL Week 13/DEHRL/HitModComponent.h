#pragma once
#include "Component.h"
// stores accumulated bonus to hit.
// hit dice and player levels fall into this category as well,
// since they make it easier to hit things. +ve is better.
// +1 sword would add 1 of these.
// -2 cursed sword would add -2 of these.
class HitModComponent :
	public Component
{
public:
	HitModComponent(int amount);
	virtual ~HitModComponent();

	// Inherited via Component
	virtual bool isType(ComponentType type) override;
	int getHitModification();
private:
	int hitModification;
};