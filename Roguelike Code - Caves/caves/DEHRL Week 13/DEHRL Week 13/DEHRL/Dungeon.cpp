#include "stdafx.h"
#include "Dungeon.h"
#include "OneRoomMap.h"
#include "GridMap.h"
#include "DEHGE.h"
#include "ScreenManager.h"
#include "Enemy.h"
#include "ItemFactory.h"
#include "Weapon.h"
#include <sstream>
#include "PlayerController.h"
#include "CaveMap.h"
Dungeon* Dungeon::instance = NULL;

// lazy access to the instance
Dungeon * Dungeon::getInstance()
{
	if (instance == NULL)
	{
		instance = new Dungeon();
	}
	return instance;
}

Dungeon::Dungeon()
{
	queue = new DungeonCommandMessageQueue();
}

Dungeon::~Dungeon()
{
}

// swap active threads when changing levels
void Dungeon::switchThreads(int currentLevel, int newLevel)
{
	// we need to do two things.  First off, halt (without killing the monsters) any
	// active threads.
	std::vector<Creature*> *creaturesOnCurrentLevel = getMapAtLevel(currentLevel)->getModel()->getCreatures();
	for each (Creature* c in (*creaturesOnCurrentLevel))
	{
		if (c->isVisible() && c->getCreatureType() == CreatureType::ENEMY)
		{
			Enemy *e = (Enemy*)c;
			e->pauseThread();
		}
	}
	// then, we need to resume any threads on the new level
	std::vector<Creature*> *creaturesOnNewLevel = getMapAtLevel(newLevel)->getModel()->getCreatures();
	for each (Creature* c in (*creaturesOnNewLevel))
	{
		if (c->isVisible() && c->getCreatureType() == CreatureType::ENEMY)
		{
			Enemy *e = (Enemy*)c;
			e->resumeThread();
		}
	}
}

// dig the entire dungeon. 
void Dungeon::initializeDungeon()
{
	ScreenID id = ScreenManager::getInstance()->getInitializingScreenID();
	// for now, we're going to start with a single, one room map level
	OneRoomMap *orm1 = new OneRoomMap();
	orm1->setLevel(1);
	maps.push_back(orm1);
	currentMapLevel = 0;
	CaveMap *cave = new CaveMap(2);
	// turn everything on in the cave map for now.

	cave->getStairsUp()->makeVisible();
	cave->getStairsDown()->makeVisible();
	maps.push_back(cave);
	// add some more levels 
	for (int l = 3; l <= 50; l++)
	{
		GridMap *gm = new GridMap(l);
		
		maps.push_back(gm);
	}
	OneRoomMap *orm = new OneRoomMap();
	orm->setLevel(51);
	// add some creatures to the maps.
	for each (Map *m in maps)
	{
		m->spawnCreatures();
		if (m->getModel()->isCaveMapModel())
		{ // caves are big.  fill them up with friends to play with.
			m->spawnCreatures();
			m->spawnCreatures();
			m->spawnCreatures();
			m->spawnCreatures();
			m->spawnCreatures();
		}
	}
	// and drop the player into the map
	player = new Player();
	PlayerController *pc = new PlayerController(player);
	int upx = orm1->getStairsUp()->getX();
	int upy = orm1->getStairsUp()->getY();
	player->setPosition(upx,upy); // this is pretty arbitrary - we know it will work
								 // because the one room map is centered around that.
	// and connect things up.
	// by registering with the game engine, update, render and keypress will be called
	DEHGE::getInstance()->addModel(id,this);
	DEHGE::getInstance()->addView(id, this);
	DEHGE::getInstance()->addKeyController(id, this);
	DEHGE::getInstance()->addKeyController(id, pc);
	// retrieve the position the player is at
	Point *playerPos = player->getPosition();
	// and set the rendering offset to that.  this will keep the player centered
	// on the screen, and the map will move instead.  We'll need to do this
	// periodically in the update method.
	DEHGE::getInstance()->setOffset(playerPos->getX(), playerPos->getY());
	// we also want the status bar to be up and running - it's going to snag
	// some data from the player, so it needs to be aware of it.
	statusbar = new StatusBar(player);
	DEHGE::getInstance()->addModel(id, statusbar);
	orm1->visit(upx, upy); // should light up the room.
}

// game logic time
void Dungeon::update(int milliseconds)
{
	// do we have a map that we're on?
	Map* m = maps[currentMapLevel];
	if (m != NULL)
	{
		// if so, get the model from the map
		Model *mod = m->getModel();
		if (mod != NULL)
		{
			// and assuming we found one, update it.
			mod->update(milliseconds);
		}
	}
	// update the offset
	Point *playerPos = player->getPosition();
	DEHGE::getInstance()->setOffset(40-(playerPos->getX()), 12-(playerPos->getY())); // center the map on the player
	// and let the player update itself.  Not currently needed, but may be important
	// later.
	player->update(milliseconds); // in case potions etc wear off after a certain number of seconds...
	// now process any outsitanding commands
	int count = queue->count(); // by doing this, any new commands added while we're updating
	// will be run in the next frame.
	for (int i = 0; i < count; i++)
	{
		DungeonCommand *command = queue->front();
		queue->pop();
		command->execute();
	}
}

// time for the render phase
void Dungeon::render()
{
	// again, get the current map
	Map* m = maps[currentMapLevel];
	if (m != NULL)
	{
		// and get that map's view
		View *v = m->getView();
		if (v != NULL)
		{
			// and draw it.
			v->render();
		}
	}
	// then draw the player on top of everything
	player->render();
	// and display the status bar.
	statusbar->render();
}

// we'll let the player handle the key press - just proxy it off to them.
void Dungeon::keyPress(int key)
{
	if (key == 27)
	{
		ScreenManager::getInstance()->popScreen();
	}
	if (key == ';')
	{
		// spawn a weapon or armor, get it's description, and test it out
		int level = rand() % 50;
		Item *item = ItemFactory::getInstance()->generateItem(level);
		player->addItem(item);
	}
}

// what map are we on
Map * Dungeon::getCurrentMap()
{
	return maps[currentMapLevel];
}

// access a random map
Map * Dungeon::getMapAtLevel(int level)
{
	return maps[level];
}

// move to a lower dungeon level
void Dungeon::moveDown()
{
	if (currentMapLevel < (int)(maps.size() - 1))
	{
		switchThreads(currentMapLevel, currentMapLevel + 1);
		currentMapLevel++;
		// need to find the matching up stairs in that level, and move the player there
		int upx = getCurrentMap()->getStairsUp()->getX();
		int upy = getCurrentMap()->getStairsUp()->getY();
		player->setPosition(upx, upy);
		getCurrentMap()->visit(upx, upy);
	}
}

// move to a higher dungeon level
void Dungeon::moveUp()
{
	if (currentMapLevel > 0)
	{
		switchThreads(currentMapLevel, currentMapLevel - 1);
		currentMapLevel--;
		// need to find the matching down stairs in that level, and move the player there.
		int downx = getCurrentMap()->getStairsDown()->getX();
		int downy = getCurrentMap()->getStairsDown()->getY();
		player->setPosition(downx, downy);
		getCurrentMap()->visit(downx, downy);
	}
	else
	{
		// the player has left the dungeon. Game over?
	}
}

void Dungeon::fallDown(int howFar)
{
	int destinationlevel = currentMapLevel + howFar;
	if (destinationlevel > 50)
	{
		destinationlevel = 50;
	}
	switchThreads(currentMapLevel, destinationlevel);
	currentMapLevel = destinationlevel;
	player->setPosition(getCurrentMap()->getRandomEmptySpace());
	getCurrentMap()->visit(player->getX(), player->getY());
}

// what dungeon level are we on now?
int Dungeon::getMapLevel()
{
	return currentMapLevel;
}

// Accessor
Player * Dungeon::getPlayer()
{
	return player;
}

StatusBar * Dungeon::getStatusBar()
{
	return statusbar;
}

DungeonCommandMessageQueue * Dungeon::getQueue()
{
	return queue;
}

bool Dungeon::getGodMode()
{
	return godMode;
}

void Dungeon::toggleGodMode()
{
	godMode = !godMode;
}
