#include "stdafx.h"
#include "ItemFactory.h"
#include "Constants.h"
#include <Windows.h>
#include "Weapon.h"
#include "WeaponDecorator.h"
#include "Sword.h"
#include "Dagger.h"
#include "Mace.h"
#include "PlusOneWD.h"
#include "FlamingWD.h"

#include "Armor.h"
#include "ArmorDecorator.h"
#include "LeatherArmor.h"
#include "Chainmail.h"
#include "Platemail.h"
#include "FireproofAD.h"
#include "PlusOneAD.h"
#include "ColdproofAD.h"
#include "Padded.h"
// singleton that spawns level specific item drops.
// when new decorators are added, this needs to be updated.
ItemFactory *ItemFactory::instance = NULL;
// private
ItemFactory::ItemFactory()
{
}

// private
ItemFactory::~ItemFactory()
{
}

// static
ItemFactory * ItemFactory::getInstance()
{
	if (instance == NULL)
	{
		instance = new ItemFactory();
	}
	return instance;
}

// create a randome loot drop
Item * ItemFactory::generateItem(int level)
{
	// first off, are we making armor or weapon
	int coin = rand() % 2; 
	if (coin == 1)
	{
		return generateArmor(level);
	}
	else
	{
		return generateWeapon(level);
	}
}

// create level appropriate armor
Item * ItemFactory::generateArmor(int level)
{
	Armor *armor = new Armor();
	int at = rand() % 3; 
	switch (at)
	{
	case 0:
		armor = new LeatherArmor(armor);
		break;
	case 1: // eventually chainmail
		armor = new Chainmail(armor);
		break;
	case 2: // and eventually plate
		armor = new Platemail(armor);
		break;
	}
	// now how many special effects does it have?
	// this will be dependent on dungeon level.
	// 0 - 10  0-1
	// 11 - 20 1-2
	// 21 - 30 2-3
	// 31 - 40 3-5
	// 40+     3-6
	int numberOfEffects = 0;
	if (level >= 0 && level <= 10)
	{
		numberOfEffects = rand() % 2;
	}
	else if (level >= 11 && level <= 20)
	{
		numberOfEffects = rand() % 2 + 1;
	}
	else if (level >= 21 && level <= 30)
	{
		numberOfEffects = rand() % 2 + 2;
	}
	else if (level >= 31 && level <= 40)
	{
		numberOfEffects = rand() % 3 + 3;
	}
	else if (level >= 41)
	{
		numberOfEffects = rand() % 4 + 3;
	}
	for (int i = 0; i < numberOfEffects; i++)
	{
		// what effect? 
		int whatEffect = rand() % 4;
		switch (whatEffect)
		{
		case 0:
			armor = new PlusOneAD(armor);
			break;
		case 1:
			armor = new FireproofAD(armor);
			break;
		case 2:
			armor = new ColdproofAD(armor);
			break;
		case 3:
			armor = new Padded(armor);
			break;
		}
	}
	return armor;
}

// generate a level appropriate weapon
Item * ItemFactory::generateWeapon(int level)
{
	Weapon *weapon = new Weapon();
	// what base type of weapon?
	int wt = rand() % 3; // all we have is sword;
	switch (wt)
	{
	case 0:
		weapon = new Sword(weapon);
		break;
	case 1: // eventually, dagger
		weapon  = new Dagger(weapon);
		break;
	case 2: // eventually, mace
		weapon = new Mace(weapon);
		break;
	}
	// now how many special effects does it have?
	// this will be dependent on dungeon level.
	// 0 - 10  0-1
	// 11 - 20 1-2
	// 21 - 30 2-3
	// 31 - 40 3-5
	// 40+     3-6
	int numberOfEffects = 0;
	if (level >= 0 && level <= 10)
	{
		numberOfEffects = rand() % 2;
	}
	else if (level >= 11 && level <= 20)
	{
		numberOfEffects = rand() % 2 + 1;
	}
	else if (level >= 21 && level <= 30)
	{
		numberOfEffects = rand() % 2 + 2;
	}
	else if (level >= 31 && level <= 40)
	{
		numberOfEffects = rand() % 3 + 3;
	}
	else if (level >= 41)
	{
		numberOfEffects = rand() % 4 + 3;
	}
	for (int i = 0; i < numberOfEffects; i++)
	{
		// what effect?  Right now, we've only got +1 and flaming
		int whatEffect = rand() % 2;
		switch (whatEffect)
		{
		case 0:
			weapon = new PlusOneWD(weapon);
			break;
		case 1:
			weapon = new FlamingWD(weapon);
			break;
		}
	}
	return weapon;
}