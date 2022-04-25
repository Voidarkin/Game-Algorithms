#include "stdafx.h"
#include "Entity.h"

int Entity::nextID = 0;
// entity - a component that in addition to having a type, may also contain other components
Entity::Entity(ComponentType type)
{
	typeOfEntity = type;
	id = nextID++;
}

Entity::~Entity()
{
}

int Entity::getID()
{
	return id;
}

bool Entity::isEntity()
{
	return true;
}

void Entity::addComponent(Component * component)
{
	components.push_back(component);
}

// wipe a single child out
void Entity::removeComponent(Component * component)
{
	for (int i = 0; i < (int)(components.size()); i++)
	{
		Component *c = components[i];
		if (c == component)
		{
			components.erase(components.begin() + i);
			return;
		}
		// recurse downwards
		if (c->isEntity())
		{
			((Entity *)c)->removeComponent(component);
		}
	}
}

// search for all children that match the type,
// using recursion to walk the componet tree
std::vector<Component*>* Entity::getAllComponentsOfType(ComponentType type)
{
	std::vector<Component *> *result = new std::vector<Component *>();
	for (int i = 0; i < (int)(components.size()); i++)
	{
		Component *c = components[i];
		if (type == ComponentType::ANY_TYPE|| c->isType(type))
		{
			result->push_back(c);
		}
		if (c->isEntity())
		{
			std::vector<Component *> *resultFromEntity = ((Entity*)c)->getAllComponentsOfType(type);
			for (int j = 0; j < (int)(resultFromEntity->size());j++)
			{
				result->push_back(resultFromEntity->at(j));
			}
			delete resultFromEntity;
		}
	}
	return result;
}

// simple clear of the vector
void Entity::removeAllComponents()
{
	components.clear();
}

bool Entity::isType(ComponentType type)
{
	return type == typeOfEntity;
}