#include "stdafx.h"
#include "InventoryScreen.h"
#include "Text.h"
#include "DEHGE.h"
#include "Inventory.h"
#include "Dungeon.h"
#include "Image.h"
// show a scrolling list of items the player has accumulated
InventoryScreen::InventoryScreen()
{
}

InventoryScreen::~InventoryScreen()
{
}

ScreenID InventoryScreen::getID()
{
	return ScreenID::INVENTORY_SCREEN;
}

void InventoryScreen::initialize()
{
	Text *t = new Text();
	t->setText("Inventory");
	t->setPosition(32, 0);
	t->useOffset(false);
	// and start getting events from the game engine
	DEHGE::getInstance()->addView(getID(), t);
	// the body
	Image *image = new Image();
	image->setImage("BodyFem.txt");
	image->setPosition(36, 5);
	image->useOffset(false);
	DEHGE::getInstance()->addView(getID(), image);


	// the magic is here
	Inventory *i = new Inventory();
	DEHGE::getInstance()->addView(getID(), i);
	DEHGE::getInstance()->addKeyController(getID(), i);
	DEHGE::getInstance()->addView(getID(), Dungeon::getInstance()->getStatusBar());
	DEHGE::getInstance()->addModel(getID(), Dungeon::getInstance()->getStatusBar());
}