#include "stdafx.h"
#include "AboutScreen.h"
#include "Text.h"
#include "DEHGE.h"
#include "AboutScreenMenu.h"
AboutScreen::AboutScreen()
{
}

AboutScreen::~AboutScreen()
{
}

// which screen are we
ScreenID AboutScreen::getID()
{
	return ScreenID::ABOUT_SCREEN;
}

// we have three lines of text, and the menu with the ok onit
void AboutScreen::initialize()
{
	// first line
	Text *t = new Text();
	t->setText("Roguelike");
	t->setPosition(32, 10);
	t->useOffset(false);
	DEHGE::getInstance()->addView(getID(), t);
	// second line
	Text *t2 = new Text();
	t2->setText("Created in 2017");
	t2->setPosition(30, 11);
	t2->useOffset(false);
	DEHGE::getInstance()->addView(getID(), t2);
	// third line
	Text *t3 = new Text();
	t3->setText("By the class of 1538");
	t3->setPosition(28, 12);
	t3->useOffset(false);
	DEHGE::getInstance()->addView(getID(), t3);
	// and the menu
	AboutScreenMenu *m = new AboutScreenMenu();
	m->initialize();
}