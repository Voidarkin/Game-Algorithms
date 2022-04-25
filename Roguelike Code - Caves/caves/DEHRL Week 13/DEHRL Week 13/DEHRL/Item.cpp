#include "stdafx.h"
#include "Item.h"
#include "ItemComponent.h"
#include "Description.h"
// base item class - subclasses have all the code
Item::Item()
{
	entity = NULL;
	equipped = false;
}

Item::~Item()
{
}

Entity * Item::getEntity()
{
	// sorta like a singleton, but not quite
	if (entity == NULL)
	{
		// make the entity
		entity = new Entity(ComponentType::ANY_TYPE);
		// now make an item componet to go under it
		ItemComponent *ic = new ItemComponent(this);
		entity->addComponent(ic);
		Description *desc = new Description(getDescription());
		entity->addComponent(desc);
		entity->addComponent(getSubComponents());
	}
	return entity;
}

void Item::setEquipped(bool equip)
{
	equipped = equip;
}

bool Item::isEquipped()
{
	return equipped;
}