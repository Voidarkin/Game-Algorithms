#include "stdafx.h"
#include "ItemComponent.h"

// used to relate a set of components back to an inventory item
ItemComponent::ItemComponent(Item *theItem)
{
	item = theItem;
}

ItemComponent::~ItemComponent()
{
}

bool ItemComponent::isType(ComponentType type)
{
	return type == ComponentType::ITEM_COMPONENT;
}

Item * ItemComponent::getItem()
{
	return item;
}