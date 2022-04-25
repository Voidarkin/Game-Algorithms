#pragma once
#include "Component.h"
#include "Item.h"
// component that keeps track of an inventory item
class ItemComponent :
	public Component
{
public:
	ItemComponent(Item *theItem);
	virtual ~ItemComponent();

	// Inherited via Component
	virtual bool isType(ComponentType type) override;
	Item *getItem();
private:
	Item *item;
};