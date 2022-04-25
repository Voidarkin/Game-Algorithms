#pragma once
#include "MapView.h"
#include "CaveMapModel.h"
class CaveMapView :
	public MapView
{
public:
	CaveMapView(CaveMapModel *m);
	~CaveMapView();
private:
	CaveMapModel *model;

	// Inherited via MapView
	virtual void render() override;
};

