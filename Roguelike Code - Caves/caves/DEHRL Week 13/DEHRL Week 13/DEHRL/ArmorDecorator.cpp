#include "stdafx.h"
#include "ArmorDecorator.h"

// armor decorator is the base class for all the other things that can be bolted onto armor
// which includes what type of armor is it.
ArmorDecorator::ArmorDecorator(Armor *a)
{
	armor = a;
}

ArmorDecorator::~ArmorDecorator()
{
}

// as a generic, use whatever we're wrapped around
std::string ArmorDecorator::getDescription()
{
	return armor->getDescription();
}