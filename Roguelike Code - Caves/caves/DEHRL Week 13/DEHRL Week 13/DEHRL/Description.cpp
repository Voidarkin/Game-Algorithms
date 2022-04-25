#include "stdafx.h"
#include "Description.h"

// a component that describes something
Description::Description(std::string desc)
{
	description = desc;
}

Description::~Description()
{
}

bool Description::isType(ComponentType type)
{
	return type == ComponentType::DESCRIPTION;
}

std::string Description::getDescription()
{
	return description;
}