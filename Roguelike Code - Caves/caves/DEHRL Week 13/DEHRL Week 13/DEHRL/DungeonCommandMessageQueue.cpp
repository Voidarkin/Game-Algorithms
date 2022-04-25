#include "stdafx.h"
#include "DungeonCommandMessageQueue.h"


DungeonCommandMessageQueue::DungeonCommandMessageQueue()
{
}


DungeonCommandMessageQueue::~DungeonCommandMessageQueue()
{
}

void DungeonCommandMessageQueue::push(DungeonCommand * command)
{
	std::lock_guard<std::mutex> lg(m);
	queue.push(command);
}

void DungeonCommandMessageQueue::pop()
{
	std::lock_guard<std::mutex> lg(m);
	queue.pop();
}

DungeonCommand * DungeonCommandMessageQueue::front()
{
	std::lock_guard<std::mutex> lg(m);
	return queue.front();
}

bool DungeonCommandMessageQueue::empty()
{
	std::lock_guard<std::mutex> lg(m);
	return queue.empty();
}

int DungeonCommandMessageQueue::count()
{
	std::lock_guard<std::mutex> lg(m);
	return queue.size();
}
