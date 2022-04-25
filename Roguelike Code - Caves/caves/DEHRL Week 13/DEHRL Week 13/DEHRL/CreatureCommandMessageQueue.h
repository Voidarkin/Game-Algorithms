#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include "CreatureCommand.h"
class CreatureCommandMessageQueue
{
public:
	CreatureCommandMessageQueue();
	~CreatureCommandMessageQueue();
	void push(CreatureCommand *command);
	// remove the first enemy state from the queue
	void pop();
	// access the first enemy state on the queue
	CreatureCommand* front();
	// is the queue empty
	bool empty();
	// flush the entire queue, returning the last entry in it
	int count();
private:
	// mutex to protect the queue from simultanious modification
	std::mutex m;
	// the actual queue that we are protecting.  Methods above are mostly
	// mutex protected versions of the api that queue supports.
	std::queue<CreatureCommand *> queue;
};

