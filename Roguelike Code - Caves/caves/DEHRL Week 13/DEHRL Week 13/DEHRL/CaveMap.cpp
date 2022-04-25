#include "stdafx.h"
#include "CaveMap.h"
#include "CaveMapModel.h"
#include "CaveMapView.h"

CaveMap::CaveMap(int level)
{
	setLevel(level);
	CaveMapModel *m = new CaveMapModel();
	model = m;
	view = new CaveMapView(m);

	StairsDown *down = new StairsDown();
	down->setPosition(getRandomEmptySpace());
	m->addStairsDown(down);
	// and up to the previoous level
	StairsUp *up = new StairsUp();
	up->setPosition(getRandomEmptySpace());
	m->addStairsUp(up);
}


CaveMap::~CaveMap()
{
}
