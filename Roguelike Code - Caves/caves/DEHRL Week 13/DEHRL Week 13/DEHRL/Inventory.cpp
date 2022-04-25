#include "stdafx.h"
#include "Inventory.h"
#include "ScreenManager.h"
#include "DEHRender.h"
#include "Dungeon.h"
#include "Item.h"
#include "Description.h"
#include <string>
#include <vector>
#include <sstream>
// inventory displays and manipulates the player inventory
Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::render()
{
	// get the items
	std::vector<Item *> *items = Dungeon::getInstance()->getPlayer()->getInventory();
	// how manyh are there
	numberOfItems = items->size();
	// empty
	if (numberOfItems == 0)
	{
		currentItem = -1;
		DEHRender::getInstance()->drawText(10, 10, "Inventory is empty", false);
		return;
	}
	// if we had nothing selected before, start at the top
	if (currentItem == -1)
	{
		currentItem = 0;
	}
	// draw up to 20 items, stopping if we run out
	for (int i = 0; i < 20; i++)
	{
		int index = topItem + i;
		if (index >= numberOfItems)
		{
			break; // we are showing the last items in the inventory
		}
		std::stringstream s;
		// draw ** in front of the current one
		if (index == currentItem)
		{
			s << "> ";
		}
		else
		{
			s << "  ";
		}
		if (items->at(index)->isEquipped())
		{
			s << "*";
		}
		else
		{
			s << " ";
		}
		// and dump out the description of each item
		s << (index+1) << " " << items->at(index)->getDescription();
		DEHRender::getInstance()->drawText(0, i+2, s.str(), false);
	}
	std::stringstream s2;
	int lastOnScreen = topItem + 20;
	if (lastOnScreen > numberOfItems)
	{
		lastOnScreen = numberOfItems;
	}
	// summarize what part of inventory is shown
	s2 << topItem + 1 << " to " << lastOnScreen << " of " << numberOfItems;
	DEHRender::getInstance()->drawText(0, 24, s2.str(), false);

	Entity *equip = Dungeon::getInstance()->getPlayer()->getEquipment();
	std::vector<Component *> *heads = equip->getAllComponentsOfType(ComponentType::HEAD);
	std::vector<Component *> *left = equip->getAllComponentsOfType(ComponentType::LEFT);
	std::vector<Component *> *right = equip->getAllComponentsOfType(ComponentType::RIGHT);
	std::vector<Component *> *body = equip->getAllComponentsOfType(ComponentType::BODY_ARMOR);

	Component *head = heads->at(0);
	Component *lefthand = left->at(0);
	Component *righthand = right->at(0);
	Component *bodyarmor = body->at(0);

	std::vector<Component *> *descriptions = head->getAllComponentsOfType(ComponentType::DESCRIPTION);
	Description *desc = (Description *)(descriptions->at(0));
	DEHRender::getInstance()->drawText(44, 4, desc->getDescription(), false);

	descriptions = lefthand->getAllComponentsOfType(ComponentType::DESCRIPTION);
	desc = (Description *)(descriptions->at(0));
	DEHRender::getInstance()->drawText(30, 12, desc->getDescription(), false);

	descriptions = righthand->getAllComponentsOfType(ComponentType::DESCRIPTION);
	desc = (Description *)(descriptions->at(0));
	DEHRender::getInstance()->drawText(60, 12, desc->getDescription(), false);

	descriptions = bodyarmor->getAllComponentsOfType(ComponentType::DESCRIPTION);
	desc = (Description *)(descriptions->at(0));
	DEHRender::getInstance()->drawText(44, 18, desc->getDescription(), false);

}

// handle keystrokes
// esc - return to whence we came
// up - select previous item
// down -  select next item
// d - drop selected item
void Inventory::keyPress(int key)
{
	if (key == 27)
	{
		ScreenManager::getInstance()->popScreen();
	}
	if (currentItem == -1)
	{
		return;
	}
	if (key == KeyboardMap::KM_UP)
	{
		if (currentItem != -1)
		{
			currentItem--;
			// if we scrolled off the top
			if (currentItem < topItem)
			{
				// mvoe the top
				topItem--;
				if (topItem < 0)
				{
					topItem = 0;
				}
				// if we went too far, stop at the top
				if (currentItem < 0)
				{
					currentItem = 0;
				}
			}

		}
	}
	if (key == KeyboardMap::KM_DOWN)
	{
		if (currentItem != -1)
		{
			currentItem++;
			// don't let them select past the number of items
			if (currentItem == numberOfItems)
			{
				currentItem--;
			}
			// and if they scroll off the bottom
			if ((currentItem - topItem )>=20)
			{
				// move the top item down a bit
				topItem++;
				
				if (topItem == numberOfItems)
				{
					topItem--;
				}
			}
		}
	}
	// if we have an item, drop it
	if (key == 'd')
	{
		std::vector<Item *> *items = Dungeon::getInstance()->getPlayer()->getInventory();
		Dungeon::getInstance()->getPlayer()->dropItem(items->at(currentItem));
		// if we discarded the final item, then select the one above it
		if (currentItem == numberOfItems - 1)
		{
			currentItem--;
		}
	}
	if (key == 'e')
	{
		std::vector<Item *> *items = Dungeon::getInstance()->getPlayer()->getInventory();
		if ((items->at(currentItem))->isEquipped() == false)
		{
			Dungeon::getInstance()->getPlayer()->equipItem(items->at(currentItem));
		}
	}
	if (key == 'u')
	{
		std::vector<Item *> *items = Dungeon::getInstance()->getPlayer()->getInventory();
		if ((items->at(currentItem))->isEquipped() == true)
		{
			Dungeon::getInstance()->getPlayer()->unequipItem(items->at(currentItem));
		}
	}
}