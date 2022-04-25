#include "stdafx.h"
#include "Component.h"

// base class for everything in the component model
Component::Component()
{
}

Component::~Component()
{
}

// by default, we don't contain other things
bool Component::isEntity()
{
	return false;
}

// since we don't contain things, if we are an instance of the type, add us to the result.
std::vector<Component*>* Component::getAllComponentsOfType(ComponentType type)
{
	std::vector<Component*>* result = new std::vector<Component*>();
	if (isType(type))
	{
		result->push_back(this);
	}
	return result;
}