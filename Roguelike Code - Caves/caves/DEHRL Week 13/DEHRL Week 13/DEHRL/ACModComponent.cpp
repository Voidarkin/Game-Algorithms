#include "stdafx.h"
#include "ACModComponent.h"

// How much does the AC change? 
ACModComponent::ACModComponent(int amount)
{
	acModification = amount;
}


ACModComponent::~ACModComponent()
{
}

// accessor
bool ACModComponent::isType(ComponentType type)
{
	return type ==ComponentType::AC_MOD;
}

// accessor
int ACModComponent::getACModification()
{
	return acModification;
}