#pragma once
#include "View.h"
// abstract base class that specific map types will subclass
class MapView :
	public View
{
public:
	MapView();
	virtual ~MapView();
	// draw the map.  How this works is up to the subclasses.
	virtual void render()=0;
};