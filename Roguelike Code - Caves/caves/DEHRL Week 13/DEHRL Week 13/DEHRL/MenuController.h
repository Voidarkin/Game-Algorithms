#pragma once
#include "MouseController.h"
#include "KeyController.h"
#include "MenuModel.h"
// menu controller receives key entries and mouse motion.
// it is controlling the state of the entire menu.
class MenuController :
	public MouseController, public KeyController
{
public:
	MenuController(MenuModel *model);
	virtual ~MenuController();

	// Inherited via KeyController
	// watches for up and down arrow keys to change the selected menu item
	virtual void keyPress(int key);

	// inherited from MouseController
	// watches for mouse movement over menu items to change the selected menu item
	void mouseMoved(int x, int y);
private:
	// container of menu items
	MenuModel *menuModel;
};