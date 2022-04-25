#include "stdafx.h"
#include "EnemyStatemessageQueue.h"

// wrapper around a queue with thread safety built in
EnemyStateMessageQueue::EnemyStateMessageQueue()
{
}

EnemyStateMessageQueue::~EnemyStateMessageQueue()
{
}

// add a state to the queue, with a size limit on the queue
void EnemyStateMessageQueue::push(EnemyState *state)
{
	std::lock_guard<std::mutex> lg(m);
	if (queue.size() == 10) // max queue size is 10. Without this, we might eat lots of ram before we actually start moving.
	{
		queue.pop(); // remove the oldest item before adding more
	}
	queue.push(state);
}

// remove an item from the queue
void EnemyStateMessageQueue::pop()
{
	std::lock_guard<std::mutex> lg(m);
	queue.pop();
}

// what is at the front of the queue
EnemyState* EnemyStateMessageQueue::front()
{
	std::lock_guard<std::mutex> lg(m);
	return queue.front();
}

// is the queue empty or not
bool EnemyStateMessageQueue::empty()
{
	std::lock_guard<std::mutex> lg(m);
	return queue.empty();
}

// discard all items from the queue, and return the final entry in it
EnemyState* EnemyStateMessageQueue::last()
{
	std::lock_guard<std::mutex> lg(m);
	EnemyState *state = NULL;
	while (queue.empty() == false)
	{
		if (state != NULL)
		{
			delete state;
			state = NULL;
		}
		state = queue.front();
		queue.pop();
	}
	return state;
}

// instead of people pushing values directly, we are notified about enemy state changes.
void EnemyStateMessageQueue::notify(Creature *c,EnemyState * state)
{
	push(state);
}