#pragma once
#include "View.h"
#include "Model.h"
#include "EnemyStateMessageQueue.h"
// enemy proxy - since enmies run in their own threads, we need something that 
// is locked in sync with thegame loop to let us draw stuff at the right time.
// the Enemy proxy is that something.
class EnemyProxy :
	public View, public Model
{
public:
	// init with data from the actual enemy, and the queue that we use to get
	// messages from it
	EnemyProxy(char c, int theX, int theY, EnemyStateMessageQueue *theQueue);
	virtual ~EnemyProxy();
	// Inherited via View
	virtual void render() override;
	// Inherited via Model
	// pulls in an enemy state from the message queue and updates x and y
	virtual void update(int milliseconds) override;
	int getX();
	int getY();
private:
	// what do we draw
	char displayChar;
	// where do we draw it
	int x;
	int y;
	// tells us when something has moved
	EnemyStateMessageQueue *queue;
};