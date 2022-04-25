#include "stdafx.h"
#include "CaveMapModel.h"
#include "Point.h"
#include <windows.h>
#include "Dungeon.h"
#include <queue>
#include <vector>
#include "Node.h"
// floor
// 0 - floor
// 1 - walls
CaveMapModel::CaveMapModel()
{
	for (int x = 0; x < CAVE_WIDTH; x++)
	{
		for (int y = 0; y < CAVE_HEIGHT; y++)
		{
			seen[x][y] = false;
			int r = rand() % 100;
			if (r < WALL_CHANCE)
			{
				floor[x][y] = 1;
			}
			else
			{
				floor[x][y] = 0;
			}

		}
	}
	regenWalls();
	iterate();
	iterate();
	iterate();
	iterate();
	iterate();
	mergeCaves();
}


CaveMapModel::~CaveMapModel()
{
}

Point * CaveMapModel::getRandomEmptySpace()
{
	Point *p = new Point();

	while (true)
	{
		int x = rand() % CAVE_WIDTH;
		int y = rand() % CAVE_HEIGHT;

		if (isWalkable(x, y))
		{
			p->setPosition(x, y);
			return p;
		}
	}
}

bool CaveMapModel::isWalkable(int x, int y)
{
	if (floor[x][y] != 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CaveMapModel::visit(int x, int y)
{
	std::vector<Creature *> *creatures = Dungeon::getInstance()->getCurrentMap()->getModel()->getCreatures();
	for each (Creature *c in (*creatures))
	{
		c->makeVisible();
	}
	// we want to add visibility to the map
	setSeen(x - 1, y - 3);
	setSeen(x,y - 3);
	setSeen(x + 1,y - 3);

	setSeen(x - 2,y - 2);
	setSeen(x - 1, y - 2);
	setSeen(x,y - 2);
	setSeen(x + 1,y - 2);
	setSeen(x + 2,y - 2);

	setSeen(x - 3,y - 1);
	setSeen(x - 2,y - 1);
	setSeen(x - 1,y - 1);
	setSeen(x,y - 1);
	setSeen(x + 1,y - 1);
	setSeen(x + 2,y - 1);
	setSeen(x + 3,y - 1);

	setSeen(x - 3,y);
	setSeen(x - 2,y);
	setSeen(x - 1,y);
	setSeen(x,y);
	setSeen(x + 1,y);
	setSeen(x + 2,y);
	setSeen(x + 3,y);

	setSeen(x - 3,y + 1);
	setSeen(x - 2,y + 1);
	setSeen(x - 1,y + 1);
	setSeen(x,y + 1);
	setSeen(x + 1,y + 1);
	setSeen(x + 2,y + 1);
	setSeen(x + 3,y + 1);

	setSeen(x - 2,y + 2);
	setSeen(x - 1,y + 2);
	setSeen(x,y + 2);
	setSeen(x + 1,y + 2);
	setSeen(x + 2,y + 2);

	setSeen(x - 1,y + 3);
	setSeen(x,y + 3);
	setSeen(x + 1,y + 3);
}

int CaveMapModel::getFloor(int x, int y)
{
	if (x < 0 || x >= CAVE_WIDTH || y < 0 || y >= CAVE_HEIGHT)
	{
		return 1; // if out of bounds, it's a wall
	}
	return floor[x][y];
}

void CaveMapModel::regenWalls()
{
	for (int x = 0; x < CAVE_WIDTH; x++)
	{
		floor[x][0] = 1;
		floor[x][CAVE_HEIGHT - 1] = 1;
	}
	for (int y = 0; y < CAVE_HEIGHT; y++)
	{
		floor[0][y] = 1;
		floor[CAVE_WIDTH - 1][y] = 1;
	}
}

int CaveMapModel::sum(int x, int y)
{
	int result = 0;
	result += floor[x - 1][y - 1];
	result += floor[x][y - 1];
	result += floor[x + 1][y - 1];

	result += floor[x - 1][y];
	result += floor[x][y];
	result += floor[x + 1][y];

	result += floor[x - 1][y + 1];
	result += floor[x][y + 1];
	result += floor[x + 1][y + 1];
	return result;
}

bool CaveMapModel::beenSeen(int x, int y)
{
	if (x < 0 || x >= CAVE_WIDTH || y < 0 || y >= CAVE_HEIGHT)
	{
		return false; // if out of bounds, it's not drawn
	}
	if (godMode)
	{
		return true;
	}
	return seen[x][y];
}

void CaveMapModel::setSeen(int x, int y)
{
	if (x < 0 || x >= CAVE_WIDTH || y < 0 || y >= CAVE_WIDTH)
	{
		return;
	}
	else
	{
		seen[x][y] = true;
	}
}


void CaveMapModel::iterate()
{
	int f[CAVE_WIDTH][CAVE_HEIGHT];
	for (int x = 0; x < CAVE_WIDTH; x++)
	{
		f[x][0] = 1;
		f[x][CAVE_HEIGHT - 1] = 1;
	}
	for (int y = 0; y < CAVE_HEIGHT; y++)
	{
		f[0][y] = 1;
		f[CAVE_WIDTH - 1][y] = 1;
	}
	for (int x = 1; x < CAVE_WIDTH - 1; x++)
	{
		for (int y = 1; y < CAVE_HEIGHT - 1; y++)
		{
			int count = sum(x, y);
			if (count >= 5)
			{
				f[x][y] = 1;
			}
			else
			{
				f[x][y] = 0;
			}
		}
	}
	for (int x = 0; x < CAVE_WIDTH; x++)
	{
		for (int y = 0; y < CAVE_HEIGHT; y++)
		{
			floor[x][y] = f[x][y];
		}
	}
}

void CaveMapModel::flood(int x, int y,int f)
{
	std::queue<Point*> q;
	Point *p = new Point();
	p->setPosition(x, y);
	q.push(p);
	while (q.empty() == false)
	{
		p = q.front();
		q.pop();
		int x = p->getX();
		int y = p->getY();
		if (floor[x][y] == 0)
		{
			floor[x][y] = f;
			if (floor[x - 1][y] == 0)
			{
				p = new Point();
				p->setPosition(x - 1, y);
				q.push(p);
			}
			if (floor[x + 1][y] == 0)
			{
				p = new Point();
				p->setPosition(x + 1, y);
				q.push(p);
			}
			if (floor[x][y - 1] == 0)
			{
				p = new Point();
				p->setPosition(x, y - 1);
				q.push(p);
			}
			if (floor[x][y + 1] == 0)
			{
				p = new Point();
				p->setPosition(x, y + 1);
				q.push(p);
			}
		}
	}
}

void CaveMapModel::mergeCaves()
{
	std::vector<Point *> points;
	int f = 2;
	for (int x = 1; x < CAVE_WIDTH - 1; x++)
	{
		for (int y = 1; y < CAVE_HEIGHT - 1; y++)
		{
			if (floor[x][y] == 0)
			{
				flood(x, y, f);
				// add this x and y to a list of known points inside a cave
				Point *p = new Point();
				p->setPosition(x, y);
				points.push_back(p);
				f++;
			}
		}
	}
	// now, assign random weights to all the walls, then start A* path finding from each area to the next
	// then go back and clean things up properly.
	for (int x = 1; x < CAVE_WIDTH - 1; x++)
	{
		for (int y = 1; y < CAVE_HEIGHT - 1; y++)
		{
			if (floor[x][y] >1)
			{
				floor[x][y] = 0;
			}
			else
			{
				floor[x][y] = (rand() % 10+15);
			}
		}
	}

	// right now, the floors should look right, and the walls will be insane.
	// floors have a value of zero. they are trivial to pass through
	// walls have a 1-10 value, indicaing how much erosion is needed to get through them. Obviously, we'd pick the path with the lowest cost.
	// it's A* time.
	// we have a vector of points. if it only has one item in it, we're done.
	// set up for path finding.

	m_Last = -1;
	int nodeCount = CAVE_WIDTH * CAVE_HEIGHT;
	m_OpenList = new Node*[nodeCount];
	m_AllNodes = new Node*[nodeCount];
	int w = CAVE_WIDTH;
	int h = CAVE_HEIGHT;

	int nodeIndex = 0;
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			Node *node = new Node(x, y, floor[x][y]);
			m_AllNodes[nodeIndex++] = node;

		}
	}

	while (points.size() > 1)
	{
		calculatePath(points.at(0)->getX(), points.at(0)->getY(), points.at(1)->getX(), points.at(1)->getY());
		digPath(points.at(0)->getX(), points.at(0)->getY(), points.at(1)->getX(), points.at(1)->getY());
		points.erase(points.begin());
	}

	// reset the walls to normal mode
	for (int x = 1; x < CAVE_WIDTH - 1; x++)
	{
		for (int y = 1; y < CAVE_HEIGHT - 1; y++)
		{
			if (floor[x][y] >1)
			{
				floor[x][y] = 1;
			}
			else
			{
				floor[x][y] = 0;
			}
		}
	}
}

// A* between point A and point B
void CaveMapModel::calculatePath(int sx, int sy, int dx, int dy)
{
	// calculate a path between source and dest.
	// add the source node to the openlist.
	Node *currentNode = getNode(sx, sy);
	for (int i = 0; i < CAVE_WIDTH*CAVE_HEIGHT; i++)
	{
		m_AllNodes[i]->reset();
		m_AllNodes[i]->setTarget(dx, dy);
	}
	m_Last = -1;
	int x = 0;
	int y = 0;
	currentNode->setParent(currentNode);
	insertNodeIntoOpenList(currentNode);
	bool areWeThereYet = false;
	while (m_Last >= 0) 
	{
		Node * node = getNodeFromOpenList();
		currentNode = node;
		moveNodeToClosedList(node);
		x = node->getX();
		y = node->getY();

		// are we there yet
		if (x == dx && y == dy)
		{ // yes. yes we are.
			areWeThereYet = true;
			break;
		}
		if (y > 1)
		{
			Node *up = getNode(x, y - 1);
			if (up->getState() != NS_CLOSED) 
			{
				if (up->getState() == NS_OPEN)
				{
					int fOfUp = currentNode->getGScore() + up->getWeight() + up->getHScore();
					if (fOfUp < up->getFScore())
					{
						removeNodeFromOpenList(up);
						up->setParent(node);
						insertNodeIntoOpenList(up);
					}
				}
				else {
					up->setParent(node);
					insertNodeIntoOpenList(up);
				}
			}
		}
		if (y<CAVE_HEIGHT - 2)
		{
			Node *down = getNode(x, y + 1);
			if (down->getState() != NS_CLOSED) 
			{
				if (down->getState() == NS_OPEN)
				{
					int fOfDown = currentNode->getGScore() + down->getWeight() + down->getHScore();
					if (fOfDown < down->getFScore())
					{
						removeNodeFromOpenList(down);
						down->setParent(node);
						insertNodeIntoOpenList(down);
					}
				}
				else 
				{
					down->setParent(node);
					insertNodeIntoOpenList(down);
				}
			}
		}
		if (x > 1)
		{
			Node *left = getNode(x - 1, y);
			if (left->getState() != NS_CLOSED) 
			{
				if (left->getState() == NS_OPEN)
				{
					int fOfLeft = currentNode->getGScore() + left->getWeight() + left->getHScore();
					if (fOfLeft < left->getFScore())
					{
						removeNodeFromOpenList(left);
						left->setParent(node);
						insertNodeIntoOpenList(left);
					}
				}
				else
				{
					left->setParent(node);
					insertNodeIntoOpenList(left);
				}
			}
		}
		if (x <CAVE_WIDTH-2)
		{
			Node *right = getNode(x + 1, y);
			if (right->getState() != NS_CLOSED) 
			{
				if (right->getState() == NS_OPEN)
				{
					int fOfRight = currentNode->getGScore() + right->getWeight() + right->getHScore();
					if (fOfRight < right->getFScore())
					{
						removeNodeFromOpenList(right);
						right->setParent(node);
						insertNodeIntoOpenList(right);
					}
				}
				else
				{
					right->setParent(node);
					insertNodeIntoOpenList(right);
				}
			}
		}
	}
}

void CaveMapModel::digPath(int sx, int sy, int dx, int dy)
{
	Node *n = getNode(dx, dy);
	Node *source = getNode(sx, sy);
	while (n != source)
	{
		floor[n->getX()][n->getY()] = 0;
		n = n->getParent();
	}

}

Node * CaveMapModel::getNodeFromOpenList()
{
	Node *result = NULL;
	if (m_Last >= 0) {
		result = m_OpenList[m_Last];
		m_Last--;
	}
	return result;
}

void CaveMapModel::insertNodeIntoOpenList(Node * node)
{
	int f = node->getFScore();
	node->setState(NS_OPEN);
	// fast first check
	if (m_Last == -1 || m_OpenList[m_Last]->getFScore() > f)
	{
		m_Last++;
		m_OpenList[m_Last] = node;
		return;
	}
	for (int i = m_Last - 1; i >= 0; i--)
	{
		if (m_OpenList[i]->getFScore() >= f)
		{
			memmove(m_OpenList + i + 2, m_OpenList + i + 1, sizeof(Node*) * (m_Last - i));
			m_OpenList[i + 1] = node;
			m_Last++;
			return;
		}
	}
	memmove(m_OpenList + 1, m_OpenList, sizeof(Node*) * (m_Last + 1));
	m_OpenList[0] = node;
	m_Last++;
}

void CaveMapModel::moveNodeToClosedList(Node * node)
{
	node->setState(NS_CLOSED);
}

Node * CaveMapModel::getNode(int x, int y)
{
	return m_AllNodes[x + y*CAVE_WIDTH];
}

void CaveMapModel::removeNodeFromOpenList(Node * node)
{
	for (int i = 0; i < m_Last; i++) {
		if (m_OpenList[i] == node)
		{ // we found the one we need to pave over.
			memmove(m_OpenList + i, m_OpenList + i + 1, sizeof(Node*) * (m_Last - i));
			break;
		}
	}

	m_Last--;
}

void CaveMapModel::reset()
{
	int nodeCount = CAVE_WIDTH * CAVE_HEIGHT;
	for (int i = 0; i < nodeCount; i++)
	{
		m_AllNodes[i]->reset();
	}
	m_Last = -1;
}

bool CaveMapModel::isCaveMapModel()
{
	return true;
}

void CaveMapModel::update(int milliseconds)
{
	MapModel::update(milliseconds);
	godMode = Dungeon::getInstance()->getGodMode();
}


std::vector<Point*>* CaveMapModel::getPathPoints(int sx, int sy, int dx, int dy)
{
	std::lock_guard<std::mutex> lg(m);
	calculatePath(sx, sy, dx, dy); // this may take a while, but since it's happening in it's own thread...

	std::vector<Point *> *results = new std::vector<Point *>();
	Node *n = getNode(dx, dy);
	Node *source = getNode(sx, sy);
	while (n != source)
	{
		Point *p = new Point();
		p->setPosition(n->getX(), n->getY());
		results->push_back(p);
		n = n->getParent();
	}
	return results;
}

