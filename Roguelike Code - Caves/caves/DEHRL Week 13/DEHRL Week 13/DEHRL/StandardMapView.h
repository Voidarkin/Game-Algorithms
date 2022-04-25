#pragma once
#include "MapView.h"
#include "StandardMapModel.h"
// Standard map view - draw rooms, hallways and corners for a given standard map model
class StandardMapView :
	public MapView
{
public:
	// our view cannot do anything unless it has a model
	StandardMapView(StandardMapModel *m);
	virtual ~StandardMapView();
	// draw the rooms, hallways and corners (if any)
	void render();
private:
	StandardMapModel *model; // the model backing this view
};