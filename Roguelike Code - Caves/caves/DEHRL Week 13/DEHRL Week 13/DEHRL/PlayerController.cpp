#include "stdafx.h"
#include "PlayerController.h"
#include "Dungeon.h"
#include "CloseCommand.h"
#include "OpenCommand.h"
#include "MoveCommand.h"
#include "RunCommand.h"
#include "MoveUpCommand.h"
#include "MoveDownCommand.h"
#include "SearchCommand.h"
#include "DisarmCommand.h"
#include "ScreenManager.h"
#include "ItemFactory.h"
#include "GodModeCommand.h"
PlayerController::PlayerController(Creature *p) :CreatureController(p)
{
}


PlayerController::~PlayerController()
{
}

void PlayerController::keyPress(int key)
{
	switch (key)
	{
	case KeyboardMap::KM_UP:
		{
			// up
			MoveCommand *m = new MoveCommand();
			m->setCreature(creature);
			m->setDirection(0, -1);
			queue->push(m);
		}
		break;
	case KeyboardMap::KM_DOWN:
		// down;
		{
			// up
			MoveCommand *m = new MoveCommand();
			m->setCreature(creature);
			m->setDirection(0, 1);
			queue->push(m);
		}
		break;
	case KeyboardMap::KM_LEFT:
		// left
		{
			// up
			MoveCommand *m = new MoveCommand();
			m->setCreature(creature);
			m->setDirection(-1, 0);
			queue->push(m);
		}
		break;
	case KeyboardMap::KM_RIGHT:
		// right
		{
			// up
			MoveCommand *m = new MoveCommand();
			m->setCreature(creature);
			m->setDirection(1, 0);
			queue->push(m);
		}
		break;
		case KeyboardMap::KM_SHIFT_UP:
		{
			// up
			RunCommand *m = new RunCommand();
			m->setCreature(creature);
			m->setDirection(0, -1);
			queue->push(m);
		}
		break;
	case KeyboardMap::KM_SHIFT_DOWN:
		// down;
		{
			// up
			RunCommand *m = new RunCommand();
			m->setCreature(creature);
			m->setDirection(0, 1);
			queue->push(m);
		}
	break;
	case KeyboardMap::KM_SHIFT_LEFT:
		// left
		{
			// up
			RunCommand *m = new RunCommand();
			m->setCreature(creature);
			m->setDirection(-1, 0);
			queue->push(m);
		}
		break;
	case KeyboardMap::KM_SHIFT_RIGHT:
		// right
		{
			// up
			RunCommand *m = new RunCommand();
			m->setCreature(creature);
			m->setDirection(1, 0);
			queue->push(m);
		}
		break;

	// Open (door, eventually chests as well)
	case 'o':
		{
			OpenCommand *oc = new OpenCommand();
			oc->init(creature->getX(), creature->getY());
			Dungeon::getInstance()->getQueue()->push(oc);
		}
		break;
	// close (door)
	case '0':
		{
			GodModeCommand *gc = new GodModeCommand();
			Dungeon::getInstance()->getQueue()->push(gc);
		}
		break;
	case 'c':
		{
			CloseCommand *cc = new CloseCommand();
			cc->init(creature->getX(), creature->getY());
			Dungeon::getInstance()->getQueue()->push(cc);
		}
		break;
	case 'i':
		ScreenManager::getInstance()->pushScreen(ScreenID::INVENTORY_SCREEN);
		break;
		// pillage - debug code to let us add extra level appropriate items to inventory
	case 'p':
		((Player *)(creature))->addItem(ItemFactory::getInstance()->generateItem(Dungeon::getInstance()->getMapLevel()));
		break;
	case '<':
		{
			MoveUpCommand *up = new MoveUpCommand();
			Dungeon::getInstance()->getQueue()->push(up);
		}
		break;
	case '>':
		{
			MoveDownCommand *down = new MoveDownCommand();
			Dungeon::getInstance()->getQueue()->push(down);
		}
		break;
	case 's':
		{
			SearchCommand *sc = new SearchCommand();
			sc->init(creature->getX(), creature->getY());
			Dungeon::getInstance()->getQueue()->push(sc);
		}
		break;
	case 'd':
		{
			DisarmCommand *dc = new DisarmCommand();
			dc->init(creature->getX(), creature->getY());
			Dungeon::getInstance()->getQueue()->push(dc);
		}
		break;
	}
}
