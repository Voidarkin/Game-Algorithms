#pragma once
#include "Trigger.h"
#include "Item.h"
// wrapper around a particular item that is lying on the ground
class LootItem :
	public Trigger
{
public:
	// we create it externally, so we can drop items on the ground near us.
	LootItem(Item *i);
	virtual ~LootItem();

	// Inherited via Trigger
	virtual void render() override;
	// let the player pick it up
	virtual void fireTrigger(Creature * c) override;
	// loot item
	virtual TriggerTypes getTriggerType() override;
	// le tthe rest of the map decide
	virtual bool isWalkable(int x, int y) override;
private:
	// what will they get
	Item *item;
};