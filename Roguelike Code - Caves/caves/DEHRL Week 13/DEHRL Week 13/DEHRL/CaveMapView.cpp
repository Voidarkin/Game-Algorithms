#include "stdafx.h"
#include "CaveMapView.h"
#include "DEHRender.h"
#include "Dungeon.h"
CaveMapView::CaveMapView(CaveMapModel *m)
{
	model = m;
}


CaveMapView::~CaveMapView()
{
}

void CaveMapView::render()
{
	int px = Dungeon::getInstance()->getPlayer()->getX();
	int py = Dungeon::getInstance()->getPlayer()->getY();

	for (int x = px-40; x < px+40; x++)
	{
		for (int y = py-10; y < py+10; y++)
		{
			if (model->getFloor(x, y) == 1)
			{
				if (model->beenSeen(x, y))
				{
					DEHRender::getInstance()->drawChar(x, y, '#', true);
				}
			}
			else
			{
				
				
				if (model->beenSeen(x, y))
				{
					DEHRender::getInstance()->drawChar(x, y, '.', true);
				}
			}
		}
	}
	std::vector<Trigger *> *triggers = model->getTriggers();
	for each (Trigger *trigger in (*triggers))
	{
		if (model->beenSeen(trigger->getX(), trigger->getY()))
		{
			trigger->render();
		}
	}
	// now, instead of drawing the creatures, we draw their proxies.
	std::vector<EnemyProxy *> *enemies = model->getEnemies();
	for each (EnemyProxy *enemy in (*enemies))
	{

		if (model->beenSeen(enemy->getX(), enemy->getY()))
		{
			enemy->render();
		}
	}
}
