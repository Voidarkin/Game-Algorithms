#include "stdafx.h"
#include "AboutScreenMenu.h"
#include "MenuItem.h"
#include "PopScreenCommand.h"
//menu on the about screen has a single ok button
AboutScreenMenu::AboutScreenMenu()
{
}

AboutScreenMenu::~AboutScreenMenu()
{
}

// add the button
void AboutScreenMenu::initialize()
{
	// make the about button
	MenuItem *ok = model->makeMenuItem();
	PopScreenCommand *pop = new PopScreenCommand();
	// set up the text and add it to the engine to run
	ok->initialize(pop);
	ok->setText("OK");
	// position and size
	ok->init(60, 20, 12, 3);
}