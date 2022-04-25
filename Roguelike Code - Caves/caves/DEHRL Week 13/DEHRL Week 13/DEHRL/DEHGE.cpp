#include "stdafx.h"
#define NCURSES_MOUSE_VERSION
#include "pdcwin.h"
#include "DEHGE.h"
#include "DEHRender.h"
#include "KeyController.h"
#include "MouseController.h"
#include "Model.h"
#include "View.h"
#include "Constants.h"
#include "ScreenManager.h"
#include <vector>

// keeps track of the one and only instance of the class
DEHGE* DEHGE::instance = NULL;

// private constructor - sets the game to actively running
DEHGE::DEHGE()
{
	running = true;
}

// private destructor - will never be called
DEHGE::~DEHGE()
{
}

// class method used to do lazy instantiation (create on first demand) of the instance.
DEHGE* DEHGE::getInstance()
{
	if (instance == NULL)
	{
		instance = new DEHGE();
	}
	return instance;
}

// called by the game bits to request that the program exit
void DEHGE::requestShutDown()
{
	running = false;
}

// used by the game loop to see if anyone has requested that we stop running
bool DEHGE::isRunning()
{
	return running;
}

// display all views
void DEHGE::render()
{
	DEHRender::getInstance()->prepareToRender(offsetX,offsetY); // offset says how much to shift everything
	// sample stuff to test rendering out
	//DEHRender::getInstance()->drawText(10, 5, "Hello World",true);
	//DEHRender::getInstance()->drawRect(12, 3, 20, 15,'#',true);
	//DEHRender::getInstance()->fillRect(22, 3, 29, 18,'#','.',true);
	//DEHRender::getInstance()->drawHLine(0, 10, 2);
	//DEHRender::getInstance()->drawVLine(1, 2, 15);
	if (displayMouse == true) {
	//	DEHRender::getInstance()->drawText(0, 0, mouseDown ? "down"+ std::to_string(downCount) : "!D:"+ std::to_string(downCount));
	//	DEHRender::getInstance()->drawText(0, 1, mouseUp? "up" : "");
		DEHRender::getInstance()->drawText(mouseX, mouseY, "+");
	}

	// the real rendering code
	// ask each view we know about to render itself
	std::vector<View *> *activeViews = views[ScreenManager::getInstance()->getCurrentScreenID()];
	if (activeViews != NULL)
	{
		for each (View * v in (*activeViews))
		{
			v->render();
		}
	}
	// and show the results to the player
	DEHRender::getInstance()->doneRendering();

}

// called each frame to give each model a chance to update itself. 
void DEHGE::update(int milliseconds)
{
	std::vector<Model *> *activeModels = models[ScreenManager::getInstance()->getCurrentScreenID()];
	if (activeModels != NULL)
	{
		for each (Model *m in (*activeModels))
		{
			m->update(milliseconds);
		}
	}
}

// receive and handle user input.
// note that this is NOT blocking - the game keeps updating even if there is no key available.
void DEHGE::processInput()
{
	// mouse input is a pain in the butt
	MEVENT event;
	// do we have a mouse event at all?
	if (getmouse(&event) == OK)
	{
		std::vector<MouseController *> *activeMouseControllers = mouseControllers[ScreenManager::getInstance()->getCurrentScreenID()];
		if (activeMouseControllers != NULL)
		{
			// has the mouse moved this frame?
			if (mouseX != event.x || mouseY != event.y)
			{
				// save where we moved to
				mouseX = event.x;
				mouseY = event.y;

				// and tell everyone (that cares) that the mouse was moved
				for each(MouseController *m in (*activeMouseControllers))
				{
					m->mouseMoved(event.x, event.y);
				}
			}
			mouseDown = false;
			mouseUp = false;
			// mouse click - eventually, we might want right click as well.  that would expand this code a bit.
			// is the left button down?
			if (event.bstate & BUTTON1_PRESSED)
			{
				mouseDown = true;
				downCount++;
				if (downCount == 1) // only call this the first frame the mouse is down
				{
					for each(MouseController *m in (*activeMouseControllers))
					{
						m->leftMouseDown(event.x, event.y);
					}
				}
			}
			// was the left button released this frame?
			else if (event.bstate & BUTTON1_RELEASED)
			{
				downCount = 0;
				mouseUp = true;
				for each(MouseController *m in (*activeMouseControllers))
				{
					m->leftMouseUp(event.x, event.y);
				}
			}
		}
	}
	// end of mouse handling, beginning of keyboard inputs
	// retrieve the key - if there is one.
	// note - keyboard repeat will result in a sequence of keys being available, but still only one per frame.
	// we are also not keeping track of key ups - yet - we may want to do that in the future
	int key = getch();
	if (key == ERR)
	{
		// no key available
	}
	else if (key == KEY_MOUSE)
	{
		// already handled - but we don't want to pester the key controllers
	}
	else {
		std::vector<KeyController *> *activeKeyControllers = keyControllers[ScreenManager::getInstance()->getCurrentScreenID()];
		if (activeKeyControllers != NULL)
		{
			// key has the valid key that was pressed this frame.
			// pass it to the key controllers
			for each (KeyController* k in (*activeKeyControllers))
			{
				k->keyPress(key);
			}
		}
		// more debug level code - if this is here, then the rendering code will request that the mouse cursor be shown.
		if (key == 265)
		{
			showMouse(!displayMouse);
		}
	}
}

// turn the mouse cursor on or off
void DEHGE::showMouse(bool show)
{
	displayMouse = show;
}

// add a model to the list of things requiring updating periodically
void DEHGE::addModel(ScreenID id, Model * m)
{
	std::vector<Model *> *modelV = models[id];
	if (modelV == NULL)
	{
		modelV = new std::vector<Model*>();
		models[id] = modelV;
	}
	modelV->push_back(m);
}

// add a view to the list of things that will need rendering
void DEHGE::addView(ScreenID id, View * v)
{
	std::vector<View *> *viewV = views[id];
	if (viewV == NULL)
	{
		viewV = new std::vector<View*>();
		views[id] = viewV;
	}
	viewV->push_back(v);
}

// add a key controller to the list of things to be told about key presses
void DEHGE::addKeyController(ScreenID id, KeyController * controller)
{
	std::vector<KeyController *> *keyControllerV = keyControllers[id];
	if (keyControllerV == NULL)
	{
		keyControllerV = new std::vector<KeyController*>();
		keyControllers[id] = keyControllerV;
	}
	keyControllerV->push_back(controller);
}

// add a mouse controller to the list of things that need to be told when the mouse moves, or is clicked
void DEHGE::addMouseController(ScreenID id, MouseController * controller)
{
	std::vector<MouseController *> *mouseControllerV = mouseControllers[id];
	if (mouseControllerV == NULL)
	{
		mouseControllerV = new std::vector<MouseController*>();
		mouseControllers[id] = mouseControllerV;
	}
	mouseControllerV->push_back(controller);
}

// used to tell the renderer how much to offset things when drawing
void DEHGE::setOffset(int x, int y)
{
	offsetX = x;
	offsetY = y;
}