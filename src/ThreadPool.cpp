/*
 * File:   ThreadPool.cpp
 * Author: buchse_a
 *
 * Created on April 18, 2015, 11:25 AM
 */

#include <queue>
#include <list>
#include <algorithm>
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
		if (!_tasks.empty() && (*thread)->getStatus() == Thread::NOTSTARTED)
		{
			(*thread)->runTask(_tasks.front());
			_tasks.pop();
		}
		if (_tasks.empty())
			break;
	}
}

std::vector<Thread::Status> ThreadPool::getStatus() const
{
	std::vector<Thread::Status> status;
	for (std::list<Thread*>::const_iterator thread = _threads.begin(); thread != _threads.end(); ++thread)
		status.push_back((*thread)->getStatus());

	return (status);
}

size_t ThreadPool::countAvailable() const
{
	std::vector<Thread::Status> status = this->getStatus();

	return (std::count(status.begin(), status.end(), Thread::NOTSTARTED));
}
