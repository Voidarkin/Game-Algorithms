#include "stdafx.h"
#include "Application.h"
#include "ScreenManager.h"
#include "GameScreen.h"
#include "SplashScreen.h"
#include "AboutScreen.h"
#include "MenuScreen.h"
#include "GameOverScreen.h"
#include "InventoryScreen.h"
// instead of digging the dungeon, we build the 4 screens.  The game screen,
// as part of it's initialization, will dig the dungeon.
Application::Application()
{
}

Application::~Application()
{
}

// create the screens
void Application::initialize()
{
	MenuScreen *m = new MenuScreen();
	m->init();
	ScreenManager::getInstance()->addScreen(m);

	AboutScreen *a = new AboutScreen();
	a->init();
	ScreenManager::getInstance()->addScreen(a);

	SplashScreen *s = new SplashScreen();
	s->init();
	ScreenManager::getInstance()->addScreen(s);

	GameScreen *g = new GameScreen();
	g->init();
	ScreenManager::getInstance()->addScreen(g);

	GameOverScreen *go = new GameOverScreen();
	go->init();
	ScreenManager::getInstance()->addScreen(go);

	InventoryScreen *in = new InventoryScreen();
	in->init();
	ScreenManager::getInstance()->addScreen(in);

	// and start with the splash screen
	ScreenManager::getInstance()->setScreen(s->getID());
}