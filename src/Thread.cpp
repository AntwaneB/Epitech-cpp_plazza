/*
 * File:   Thread.cpp
 * Author: buchse_a
 *
 * Created on April 10, 2015, 9:59 PM
 */

#include <stdexcept>
#include "Thread.hpp"

Thread::Thread()
	: _status(NOTSTARTED)
{
}

Thread::~Thread()
{
	if (_status == Thread::RUNNING)
	{
		this->stop(NULL);
	}
}

Thread::Status Thread::getStatus() const
{
	return (_status);
}

void Thread::run(void* (*startRoutine)(void*), void* routineArg)
{
	if (_status == Thread::RUNNING)
		throw Thread::Exception("Thread::run : Trying to run already running thread.");
	else if (_status == Thread::DEAD)
		throw Thread::Exception("Thread::run : Trying to re-run dead thread.");

	_status = Thread::RUNNING;
	if (pthread_create(&_thread, NULL, startRoutine, routineArg) != 0)
		throw Thread::Exception(std::string("pthread_create") + strerror(errno));
}

void* Thread::wait(void)
{
	if (_status != Thread::RUNNING)
		throw Thread::Exception("Thread::wait : Trying to wait for a non-started thread.");

	void*	ret;
	if (pthread_join(_thread, &ret) != 0)
		throw Thread::Exception(std::string("pthread_join") + strerror(errno));

	_status = Thread::DEAD;
	return (ret);
}

void Thread::stop(void* retValue)
{
	if (_status != Thread::RUNNING)
		throw Thread::Exception("Thread::stop : Trying to stop a non-started thread.");

	_status = Thread::DEAD;
	pthread_exit(retValue);
}

void Thread::runTask(ITask* task)
{
	_task = task;

	if (_status == Thread::RUNNING)
		throw Thread::Exception("Thread::runTask : Trying to run already running thread.");
	else if (_status == Thread::DEAD)
		throw Thread::Exception("Thread::runTask : Trying to re-run dead thread.");

	_status = Thread::RUNNING;
	if (pthread_create(&_thread, NULL, &Thread::threadRunner, this) != 0)
		throw Thread::Exception(std::string("pthread_create") + strerror(errno));
}

void* Thread::threadRunner(void* arg)
{
	Thread* thread = static_cast<Thread*>(arg);
	std::cout << "Coucou" << std::endl;
	thread->_task->execute();
	thread->_status = Thread::NOTSTARTED;

	return (NULL);
}
