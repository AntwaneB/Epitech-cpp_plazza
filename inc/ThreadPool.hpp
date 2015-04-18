/*
 * File:   ThreadPool.hpp
 * Author: buchse_a
 *
 * Created on April 18, 2015, 11:25 AM
 */

#ifndef THREADPOOL_HPP
#define	THREADPOOL_HPP

#include "ITask.hpp"
#include "Thread.hpp"

class ThreadPool
{
public:
	ThreadPool();
	virtual ~ThreadPool();

	void	pushTask(ITask*);

private:
	std::list<Thread*>	_threads;
	std::queue<ITask*>	_tasks;
};

#endif	/* THREADPOOL_HPP */
