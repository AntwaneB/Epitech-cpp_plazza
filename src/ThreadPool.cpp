/*
 * File:   ThreadPool.cpp
 * Author: buchse_a
 *
 * Created on April 18, 2015, 11:25 AM
 */

#include <queue>
#include <list>

#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		_threads.push_back(new Thread);
	}
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::pushTask(ITask* task)
{
	_tasks.push(task);
}

void ThreadPool::runTasks()
{
	for (std::list<Thread*>::iterator thread = _threads.begin(); thread != _threads.end(); ++thread)
	{
		if ((*thread)->getStatus() == Thread::NOTSTARTED)
		{
			(*thread)->runTask(_tasks.front());
			_tasks.pop();
		}
	}
}
