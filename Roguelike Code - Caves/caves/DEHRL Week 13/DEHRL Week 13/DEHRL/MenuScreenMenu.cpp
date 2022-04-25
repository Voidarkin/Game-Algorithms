#include "stdafx.h"
#include "MenuScreenMenu.h"
#include "MenuItem.h"
#include "QuitCommand.h"
#include "PushScreenCommand.h"

MenuScreenMenu::MenuScreenMenu()
{
}

MenuScreenMenu::~MenuScreenMenu()
{
}

// the menu on the menu screen has 3 menu items on it. play, about and quit
void MenuScreenMenu::initialize()
{
	// create the play menu item
	MenuItem *play = model->makeMenuItem();
	PushScreenCommand *push = new PushScreenCommand();
	push->setScreenID(ScreenID::GAME_SCREEN);
	play->initialize(push);
	play->setText("PLAY");
	play->init(34, 5, 12, 5);
	// create the about menu item
	MenuItem *about = model->makeMenuItem();
	push = new PushScreenCommand();
	push->setScreenID(ScreenID::ABOUT_SCREEN);
	about->initialize(push);
	about->init(34, 11, 12, 5);
	about->setText("ABOUT");
	model->addMenuItem(about);
	// create the quit menu item
	MenuItem *quit = model->makeMenuItem();
	QuitCommand *q = new QuitCommand();
	quit->initialize(q);
	quit->setText("QUIT");
	quit->init(34, 17, 12, 5);
	model->addMenuItem(quit);
}