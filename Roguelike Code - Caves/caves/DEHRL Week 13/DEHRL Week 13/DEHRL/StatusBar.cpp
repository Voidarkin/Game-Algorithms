#include "stdafx.h"
#include "StatusBar.h"
#include "DEHRender.h"
#include "Point.h"
#include <sstream>
#include "Dungeon.h"

// the status bar requires the player, so pass it in when constucted
StatusBar::StatusBar(Player *p)
{
	// and then save it
	player = p;
}

StatusBar::~StatusBar()
{
}

// draw the status bar area
void StatusBar::render()
{
	// clear the space at the bottom two rows
	DEHRender::getInstance()->fillRect(0, 23, 79, 24, ' ', ' ', false);
	if (player != NULL)
	{
		// retrieve data from the player
		long hp = player->getHP();
		long maxhp = player->getMaxHP();
		Point *pos = player->getPosition();
		int playerLevel = player->getHitDice();
		int playerXP = player->getXP();
		int gold = player->getGold();
		int level = Dungeon::getInstance()->getMapLevel() + 1; // +1 cause plaeyrs don't always get 0 based arrays
															   // and display the data
		std::stringstream s1;
		s1 << "dungeon level: " << level << " hp: " << hp << "/" << maxhp << " AC: " << player->getAC() << " level: " << playerLevel << " xp: " << playerXP;
		s1 << " gp: " << gold << " x:" << player->getX() << " y:" << player->getY();
		DEHRender::getInstance()->drawText(0, 23, s1.str(), false);
		if (message.length() != 0)
		{
			DEHRender::getInstance()->drawText(0, 24, message, false);
		}
	}

}

void StatusBar::setMessage(std::string m)
{
	message = m;
	timeMessageHasBeenShown = 0;
}

// times out the extra message text at the bottom
void StatusBar::update(int milliseconds)
{
	timeMessageHasBeenShown += milliseconds;
	if (timeMessageHasBeenShown > MESSAGE_TIME)
	{
		setMessage("");
	}
}