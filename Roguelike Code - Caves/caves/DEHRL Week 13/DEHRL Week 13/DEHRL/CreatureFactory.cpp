#include "stdafx.h"
#include "CreatureFactory.h"
#include "Enemy.h"
#include "Bat.h"
#include "Entity.h"
#include "ACModComponent.h"
#include "HitModComponent.h"
#include "ProtectionComponent.h"
#include "Component.h"
#include "Constants.h"
#include "DamageComponent.h"
#include "StandardAIStrategy.h"
#include "BatAIStrategy.h"
// the one and only creature factory
CreatureFactory *CreatureFactory::instance = NULL;

// get the factory using lazy instantiation
CreatureFactory * CreatureFactory::getInstance()
{
	if (instance == NULL)
	{
		instance = new CreatureFactory();
	}
	return instance;
}

// try to spawn a creature (or creatures) that are appropriate for the level
void CreatureFactory::spawnMonster(int level)
{
	// to create a monster, we need to pick one from the current levels.

	// pick a starting point at random, and loop until we find a monster that is
	// valid for that level
	int selectedEnemy = -1;
	int index = rand() % 26;
	// from here to the bottom
	while (selectedEnemy == -1 && index < 26)
	{
		int min = attributes[index][5]; // need a constant
		int max = attributes[index][6]; // need a constant
		if (level >= min && level <= max)
		{
			selectedEnemy = index;
			break;
		}
		index++;
	}
	// and back to the top again (if needed)
	index = 0;
	while (selectedEnemy == -1 && index < 26)
	{
		int min = attributes[index][5]; // need a constant
		int max = attributes[index][6]; // need a constant
		if (level >= min && level <= max)
		{
			selectedEnemy = index;
			break;
		}
		index++;
	}
	// we now have our enemy data - it's at selectedEnemy in the vectors
	// once populated, add it (and maybe it's friends)
	// to that dungeon maps list of creatures
	// how many should we spawn?
	int lowNum = attributes[selectedEnemy][7]; // need a constant
	int highNum = attributes[selectedEnemy][8]; // need a constant
	int numToAdd = rand() % (highNum - lowNum + 1) + lowNum;
	for (int i = 0; i < numToAdd; i++)
	{
		Enemy *e = NULL;
		if (selectedEnemy == 1) // special case code for spawning subclass of enemy
		{
			e = new Bat();
			BatAIStrategy *bs = new BatAIStrategy();
			bs->setCreature(e);
			e->setStrategy(bs);

		}
		else
		{
			e = new Enemy();
			StandardAIStrategy *ss = new StandardAIStrategy();
			ss->setCreature(e);
			e->setStrategy(ss);
		}
		e->setName(names[selectedEnemy]);
		e->setChar(attributes[selectedEnemy][0]); // need a constant
		int hd = attributes[selectedEnemy][1]; // need a constant
		e->setHitDice(hd);
		int hp = 0;
		// roll hit points
		for (int j = 0; j < hd; j++)
		{
			hp += rand() % 8 + 1;
		}
		// bats are zero HD creatures, that have 1-4 hit points.
		if (hp == 0) // bats.  go figure.
		{
			hp = rand() % 4 + 1;
		}
		// save the hit points
		e->setMaxHP(hp);
		// how much damage does it do when it hits
		e->setDamage(attributes[selectedEnemy][2], attributes[selectedEnemy][3]); // need a constant
		e->setAC(attributes[selectedEnemy][4]);// need a constant
		e->setFrameDelay(attributes[selectedEnemy][9]); // how long do we sleep between moves
		// now add it's attack, protection and vulnerability (if any)
		Entity *equipment = e->getEquipment();
		ACModComponent *acMod = new ACModComponent(e->getAC());
		equipment->addComponent(acMod);
		DamageComponent *damage = new DamageComponent((DamageType)(attributes[selectedEnemy][10]), attributes[selectedEnemy][2], attributes[selectedEnemy][3]);
		equipment->addComponent(damage);
		ProtectionComponent *protection = new ProtectionComponent((DamageType)(attributes[selectedEnemy][11]), (float)(attributes[selectedEnemy][12]) / 100.0f);
		equipment->addComponent(protection);
		ProtectionComponent *vulnerability = new ProtectionComponent((DamageType)(attributes[selectedEnemy][13]), -(float)(attributes[selectedEnemy][14]) / 100.0f);
		equipment->addComponent(vulnerability);
		HitModComponent *hitMod = new HitModComponent(hd);
		equipment->addComponent(hitMod);
		// and add the creature to the dungeon at the appropriate level
		Dungeon::getInstance()->getMapAtLevel(level - 1)->addCreature(e);
	}
}

CreatureFactory::~CreatureFactory()
{
}
// 0 - Char on map
// 1 - hit dice (0 == d4, everything else is number of d8's)
// 2,3 - damage (#/dice)
// 4 - ac
// 5 - min level found on
// 6 - max level found on
// 7,8 - typical number found
// 9 - time to sleep between moves in milliseconds
// 10 - the type of damage they inflict
// 11 - the type of damage they protect against (if any)
// 12 - how well they do at protection against it
// 13 - the type of damage they are vulnerable to
// 14 - how well they protect against it
// monster xp is 10 x their hp.
// xp also earned for picking up treasure - 1 xp per gp
// 2,000 xp will level the player up

// set up the core data structures for generating monsters
// note - all of these values could be (and should be) read in from a data file.
CreatureFactory::CreatureFactory()
{
	names.push_back("Alligator");
	attributes.push_back(std::vector<int> { 'A', 3, 4, 4, 5, 5, 20, 1, 2, 500, PIERCING,ANY,25,NONE,0});
	names.push_back("Bat");
	attributes.push_back(std::vector<int> { 'B', 0, 1, 3, 6, 1, 10, 1, 6, 80,PIERCING,NONE,0,NONE,0});
	names.push_back("Centaur");
	attributes.push_back(std::vector<int> { 'C', 4, 2, 6, 5, 10, 25, 1, 3, 200, EDGED,NONE,0,NONE,0});
	names.push_back("Dragon");
	attributes.push_back(std::vector<int> { 'D', 12, 5, 8, -1, 35, 50, 1, 1, 500,FIRE,FIRE,90,ICE,25});
	names.push_back("Ettin");
	attributes.push_back(std::vector<int> { 'E', 10, 4, 8, 3, 25, 45, 1, 2, 1000,BLUNT,NONE,0,NONE,0});
	names.push_back("Giant Frog");
	attributes.push_back(std::vector<int> { 'F', 3, 3, 6, 7, 5, 20, 1, 2, 300,BLUNT,NONE,0,FIRE,25});
	names.push_back("Griffin");
	attributes.push_back(std::vector<int> { 'G', 7, 3, 8, 3, 25, 45, 1, 1, 250,PIERCING,BLUNT,25,FIRE,25});
	names.push_back("Hobgoblin");
	attributes.push_back(std::vector<int> { 'H', 2, 1, 8, 5, 2, 20, 1, 6, 350,EDGED,NONE,0,NONE,0});
	names.push_back("Ice Monster");
	attributes.push_back(std::vector<int> { 'I', 5, 2, 8, 8, 15, 30, 1, 1, 2000,ICE,ICE,90,FIRE,90});
	names.push_back("Jaguar");
	attributes.push_back(std::vector<int> { 'J', 4, 3, 6, 6, 10, 25, 1, 1, 125,PIERCING,NONE,0,NONE,0});
	names.push_back("Kobold");
	attributes.push_back(std::vector<int> { 'K', 1, 1, 4, 7, 1, 10, 3, 10, 380,BLUNT,NONE,0,NONE,0});
	names.push_back("Lizard");
	attributes.push_back(std::vector<int> { 'L', 4, 1, 8, 5, 10, 25, 1, 1, 500,PIERCING,NONE,0,NONE,0});
	names.push_back("Minotaur");
	attributes.push_back(std::vector<int> { 'M', 6, 2, 4, 6, 20, 40, 1, 1, 500,EDGED,NONE,0,NONE,0});
	names.push_back("Nymph");
	attributes.push_back(std::vector<int> { 'N', 3, 1, 3, 9, 5, 20, 1, 1, 80,MAGIC,NONE,0,FIRE,25});
	names.push_back("Orc");
	attributes.push_back(std::vector<int> { 'O', 1, 1, 8, 6, 1, 10, 3, 10, 950,EDGED,NONE,0,NONE,0});
	names.push_back("Phantom");
	attributes.push_back(std::vector<int> { 'P', 7, 3, 10, 0, 25, 45, 1, 1, 500,MAGIC,ANY,80,MAGIC,80});
	names.push_back("Quasit");
	attributes.push_back(std::vector<int> { 'Q', 3, 3, 3, 2, 5, 20, 1, 1, 150,PIERCING,NONE,0,NONE,0});
	names.push_back("Rattlesnake");
	attributes.push_back(std::vector<int> { 'R', 4, 2, 6, 5, 10, 25, 1, 1, 125,PIERCING,NONE,0,NONE,0});
	names.push_back("Skeleton");
	attributes.push_back(std::vector<int> { 'S', 1, 1, 6, 7, 1, 15, 1, 10, 400,EDGED,PIERCING,50,BLUNT,50});
	names.push_back("Troll");
	attributes.push_back(std::vector<int> { 'T', 6, 5, 6, 4, 20, 40, 1, 4, 600,PIERCING,NONE,0,FIRE,100});
	names.push_back("Unicorn");
	attributes.push_back(std::vector<int> { 'U', 4, 4, 6, 2, 10, 25, 1, 1, 250,PIERCING,NONE,0,NONE,0});
	names.push_back("Vampire");
	attributes.push_back(std::vector<int> { 'V', 8, 3, 10, 1, 30, 50, 1, 1, 150,PIERCING,ANY,70,MAGIC,30});
	names.push_back("Wraith");
	attributes.push_back(std::vector<int> { 'W', 5, 1, 6, 4, 15, 30, 1, 1, 750,MAGIC,ANY,80,MAGIC,80});
	names.push_back("Xorn");
	attributes.push_back(std::vector<int> { 'X', 7, 7, 3, -2, 30, 50, 1, 1, 900,BLUNT,EDGED,50,NONE,0});
	names.push_back("Yeti");
	attributes.push_back(std::vector<int> { 'Y', 4, 2, 6, 6, 10, 25, 1, 1, 500,PIERCING,ICE,80,FIRE,25});
	names.push_back("Zombie");
	attributes.push_back(std::vector<int> { 'Z', 2, 1, 8, 8, 1, 20, 1, 8, 800,BLUNT,BLUNT,25,EDGED,25});
}