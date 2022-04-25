#include "stdafx.h"
#include "CreatureCommandMessageQueue.h"


CreatureCommandMessageQueue::CreatureCommandMessageQueue()
{
}


CreatureCommandMessageQueue::~CreatureCommandMessageQueue()
{
}

void CreatureCommandMessageQueue::push(CreatureCommand * command)
{
	std::lock_guard<std::mutex> lg(m);
	queue.push(command);
}

void CreatureCommandMessageQueue::pop()
{
	std::lock_guard<std::mutex> lg(m);
	queue.pop();
}

CreatureCommand * CreatureCommandMessageQueue::front()
{
	std::lock_guard<std::mutex> lg(m);
	return queue.front();
}

bool CreatureCommandMessageQueue::empty()
{
	std::lock_guard<std::mutex> lg(m);
	return queue.empty();
}

int CreatureCommandMessageQueue::count()
{
	std::lock_guard<std::mutex> lg(m);

	return queue.size();
}
