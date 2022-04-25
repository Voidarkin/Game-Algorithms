// DEHRL.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "pdcwin.h"
#include "windows.h"
#include "Application.h"
#include "DEHGE.h"
#include <time.h>
#include <iostream>
#include <fstream>
// function declarations

// setup the pd curses library
void setupCurses();

// clean up the pd curses library
void shutdownCurses();

// app is the game specific application code - it really knows about what is happening.
// if I were to make a different game, that would be triggered in there.
Application *app;

// entry point of the application
int main()
{

	srand((unsigned int)(time(NULL)));
	
	// Initialize the primary Curses library
	setupCurses();

	// Initialize the game
	app = new Application();
	// initialize will, amoungst other things, add models, views and controllers to the game engine.  those will
	// in turn be executed in the loop beflow.
	app->initialize();

	// start up the game loop
	while (DEHGE::getInstance()->isRunning()) // as long as someone hasn't requested that we quit
	{
		// input
		DEHGE::getInstance()->processInput();
		// update
		DEHGE::getInstance()->update(16);
		// render
		DEHGE::getInstance()->render();
		// so we're not pounding the cpu.  Eventually, this would be based on actual elapsed time, not an arbitrary amount.
		// effectively, we've locked out text based game to 10 FPS
		Sleep(16);
	}

	// Close off the curses library
	shutdownCurses();
    exit(0); // need to halt all the threads.
}

// Set up curses library to allow us access to the screen and keyboard
void setupCurses()
{
	initscr();
	noecho();
	cbreak();
	timeout(0);
	keypad(stdscr, true);
	mousemask(BUTTON1_PRESSED|BUTTON1_RELEASED , NULL);
}

// close off the curses window library
void shutdownCurses()
{
	endwin();
}