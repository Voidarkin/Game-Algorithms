#pragma once
#include "Constants.h"
#include <vector>
// base class for all things that go in entities.
// the get method recursively retrieves all matching elements.
class Component
{
public:
	Component();
	virtual ~Component();
	virtual bool isEntity();
	virtual bool isType(ComponentType type) = 0;
	// recurse down all containment (if any) and build a vector of results.
	virtual std::vector<Component *> *getAllComponentsOfType(ComponentType type);
};