#pragma once
#include "Component.h"
#include <string>
// wrapper around a string that gives info about the item
class Description :
	public Component
{
public:
	Description(std::string desc);
	virtual ~Description();

	// Inherited via Component
	virtual bool isType(ComponentType type) override;
	// accessor
	std::string getDescription();
private:
	std::string description;
};