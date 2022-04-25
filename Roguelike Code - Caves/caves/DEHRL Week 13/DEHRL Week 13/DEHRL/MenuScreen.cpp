#include "stdafx.h"
#include "MenuScreen.h"
#include "Text.h"
#include "DEHGE.h"
#include "MenuScreenMenu.h"
MenuScreen::MenuScreen()
{
}

MenuScreen::~MenuScreen()
{
}

// which screen are we
ScreenID MenuScreen::getID()
{
	return ScreenID::MENU_SCREEN;
}

// set up the screen - a title area, and a 3 item menu
void MenuScreen::initialize()
{
	// title of the game
	Text *t = new Text();
	t->setText("Roguelike");
	t->setPosition(35, 3);
	t->useOffset(false);
	DEHGE::getInstance()->addView(getID(), t);
	// and the menu
	MenuScreenMenu *m = new MenuScreenMenu();
	m->initialize();
}