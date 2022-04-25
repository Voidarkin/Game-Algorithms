#pragma once
#include "View.h"
#include "Model.h"
#include "KeyController.h"
#include "Map.h"
#include <vector>
#include "Player.h"
#include "StatusBar.h"
#include "DungeonCommandMessageQueue.h"
// Dungeon is an all in one - it's the active thing that is managing our game.
// it has a number of maps one of which is currently being displayed to the user.
// it proxies most of it's callbacks off to the current map
class Dungeon :public Model, public View, public KeyController
{
public:
	// too many things need to find the one and only dungeon, so lets just make it a
	// singleton
	static Dungeon *getInstance();
	// dig the dungeon.  For this week, we start off in a nice clean one room map
	void initializeDungeon();
	// model methods
	// let the map move things around if need be.
	void update(int milliseconds);
	// view methods
	// draw the current dungeon
	void render();
	// key controller methods
	// deal with key presses
	void keyPress(int key);
	// now that we have different levels, we need to know which one we're on
	Map *getCurrentMap();
	// what is a map at a particular level (in case we go down a trapdoor or something)
	Map* getMapAtLevel(int level);
	// move down a level in the dungeon - switch to the next map
	void moveDown();
	// move up a level in the dungeon - switch to the previous map
	void moveUp();
	// how deep are we currently
	void fallDown(int howFar);
	int getMapLevel();
	// accessor
	Player* getPlayer();
	// accessor
	StatusBar* getStatusBar();
	DungeonCommandMessageQueue *getQueue();
	bool getGodMode();
	void toggleGodMode();
private:
	// the one and only dungeon
	static Dungeon *instance;
	Dungeon();
	virtual ~Dungeon();
	// the entire dungeon
	std::vector<Map *> maps;
	// index into the maps vector - where is the player currently
	int currentMapLevel;
	// the player character
	Player *player;
	// the status bar - this will always be shown  overtop of whatever 
	// map is up - it takes the bottom two lines of the screen.
	StatusBar *statusbar;
	// pause threads of monsters on current level, resume them on new level.
	void switchThreads(int currentLevel, int newLevel);
	DungeonCommandMessageQueue *queue;
	bool godMode = false;
};