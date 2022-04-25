#pragma once
#include "MapModel.h"
#include "Constants.h"
#include "Node.h"
#include "Point.h"
#include <mutex>
#include <vector>

class CaveMapModel :
	public MapModel
{
public:
	CaveMapModel();
	virtual ~CaveMapModel();

	// Inherited via MapModel
	virtual Point * getRandomEmptySpace() override;
	virtual bool isWalkable(int x, int y) override;
	void visit(int x, int y);
	int getFloor(int x, int y);
	void iterate();
	void regenWalls();
	int sum(int x, int y);
	bool beenSeen(int x, int y);
	void setSeen(int x, int y);
	void flood(int x, int y, int f);
	void mergeCaves();
	void digPath(int sx, int sy, int dx, int dy);
	void calculatePath(int sx, int sy, int dx, int dy);
	Node* getNodeFromOpenList();
	void insertNodeIntoOpenList(Node *node);
	void moveNodeToClosedList(Node *node);
	Node* getNode(int x, int y);
	void removeNodeFromOpenList(Node *node);
	void reset();
	virtual bool isCaveMapModel();
	virtual void update(int milliseconds) override;
	std::vector<Point *> *getPathPoints(int sx, int sy, int dx, int dy);
protected:
	int floor[CAVE_WIDTH][CAVE_HEIGHT];
	bool seen[CAVE_WIDTH][CAVE_HEIGHT];

private:
	bool godMode = false;
	Node** m_OpenList;
	int m_Last;
	int m_DestinationX;
	int m_DestinationY;
	int m_StartX;
	int m_StartY;
	Node** m_AllNodes;
	std::mutex m;
};

