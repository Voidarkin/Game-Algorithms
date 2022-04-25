#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include "EnemyState.h"
#include "CreatureObserver.h"
// a pipe between the enemy threads and the main game loop
// is notified when the enemy it is watching moves.
class EnemyStateMessageQueue : public CreatureObserver
{
public:
	EnemyStateMessageQueue();
	virtual ~EnemyStateMessageQueue();
	// add an enemy state to the queue
	void push(EnemyState *state);
	// remove the first enemy state from the queue
	void pop();
	// access the first enemy state on the queue
	EnemyState* front();
	// is the queue empty
	bool empty();
	// flush the entire queue, returning the last entry in it
	EnemyState* last();
	virtual void notify(Creature *c,EnemyState * state) override;
private:
	// mutex to protect the queue from simultanious modification
	std::mutex m;
	// the actual queue that we are protecting.  Methods above are mostly
	// mutex protected versions of the api that queue supports.
	std::queue<EnemyState *> queue;

	// Inherited via CreatureObserver
};