#pragma once
#include "Component.h"
#include "Constants.h"
#include <vector>
// entity is a component that can hold other components, and has a type and a unique id
class Entity :
	public Component
{
public:
	Entity(ComponentType type);
	virtual ~Entity();
	int getID();
	virtual bool isEntity();
	// add and remove individual components
	void addComponent(Component *component);
	void removeComponent(Component *component);
	// recursively find subcomponents of a given type
	virtual std::vector<Component *> *getAllComponentsOfType(ComponentType type);
	// clear out everything under us
	void removeAllComponents();
	// Inherited via Component
	virtual bool isType(ComponentType type) override;
private:
	static int nextID;
	int id;
	ComponentType typeOfEntity;
	std::vector<Component *> components;
};