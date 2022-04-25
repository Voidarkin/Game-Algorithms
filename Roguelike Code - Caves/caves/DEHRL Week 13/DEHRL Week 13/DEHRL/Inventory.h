#pragma once
#include "View.h"
#include "KeyController.h"
// manages the scrolling area of inventory on the screen
class Inventory :
	public View, public KeyController
{
public:
	Inventory();
	virtual ~Inventory();

	// Inherited via View
	// draw the scrolly list
	virtual void render() override;

	// Inherited via KeyController
	// up down, drop - eventually will also have equip
	virtual void keyPress(int key) override;
private:
	// which item is selected
	int currentItem = -1;
	// how many items are there in total
	int numberOfItems = 0;
	// which item is the first one on the screen
	int topItem = 0;
};