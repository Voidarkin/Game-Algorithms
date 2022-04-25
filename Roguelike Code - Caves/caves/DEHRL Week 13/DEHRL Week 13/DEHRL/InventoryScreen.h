#pragma once
#include "Screen.h"
// show the player what they are carying.  NOTE
// this does NOT halt the mosnter threads when running - you can be killed
// while going through your backpack
class InventoryScreen :
	public Screen
{
public:
	InventoryScreen();
	virtual ~InventoryScreen();

	// Inherited via Screen
	virtual ScreenID getID() override;
	virtual void initialize() override;
};