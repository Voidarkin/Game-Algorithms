#pragma once
class KeyController;
class MouseController;
class View;
class Model;
#include <vector>
#include "Constants.h"
#include <map>

// our core game engine code. 
// this is completely game independent - building a new game, this should NOT
// need to be altered at all. That said, we'll still be adding new fatures to it
// as the semester proceeds.
class DEHGE
{
public:
	// there can only be one game engine - you use this to get to it.
	static DEHGE* getInstance();
	// application specific code can call this to signal that we want to stop the game
	void requestShutDown();
	// called from the game loop to see if someone has requested a shutdown.
	bool isRunning();
	// called from the game loop to request that all views in the game perform their rendering
	void render();
	// called from the game loop to request that all models in the game update based on frame elapsed time
	void update(int milliseconds);
	// called from the game loop to request that all key and mouse events are handled
	void processInput();
	// utility method used to show (or hide) the mouse cursor
	void showMouse(bool show);
	// add a model to the list of models
	void addModel(ScreenID id, Model *m);
	// add a view to the lsit of views
	void addView(ScreenID id, View *v);
	// add a key controller to the list of key controllers
	void addKeyController(ScreenID id, KeyController *controller);
	// add a mouse controller to the list of mouse controllers
	void addMouseController(ScreenID id, MouseController *controller);
	// set the offset to be used by the renderer to slides things around the screen.
	void setOffset(int x, int y);
private:
	DEHGE();
	virtual ~DEHGE();
	// the one and only game engine instance
	static DEHGE* instance;
	// the offsets to draw things
	int offsetX = 0;
	int offsetY = 0;
	// is the game still running?
	bool running;
	// vector of key controllers
	std::map<ScreenID, std::vector<KeyController *>*> keyControllers;
	// vector of mouse controllers
	std::map<ScreenID, std::vector<MouseController *>*> mouseControllers;
	// vector of active views
	std::map<ScreenID, std::vector<View *>*> views;
	// vector of active models
	std::map<ScreenID, std::vector<Model *>*> models;
	// is the left mouse button down this frame?
	bool mouseDown = false;
	// is the left mouse button up this frame
	bool mouseUp = false;
	// mouse coordinates (in characters, not pixels)
	int mouseX = -1;
	int mouseY = -1;
	// how many frames has the mouse been held down
	int downCount = 0;
	// do we need to draw the mouse cursor?
	bool displayMouse = false;
};