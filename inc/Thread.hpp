/*
 * File:   Thread.hpp
 * Author: buchse_a
 *
 * Created on April 10, 2015, 9:58 PM
 */

#ifndef THREAD_HPP
#define	THREAD_HPP

#include <string>
#include <stdexcept>
#include <string.h>
#include <errno.h>
#include <pthread.h>

class Thread
{
public:
	enum Status { RUNNING, NOTSTARTED, DEAD };

public:
	class Exception : public std::runtime_error
	{
	public:
		Exception(std::string const & s) : std::runtime_error(s), _message(s) {};
		virtual ~Exception() throw() {};
		virtual const char* what() const throw() { return (_message.c_str()); }

	protected:
		std::string _message;
	};

public:
	Thread();
	virtual ~Thread();

	void run(void* (*startRoutine)(void*), void* routineArg);
	void* wait(void);
	void stop(void* retValue);

	Thread::Status	getStatus(void) const;

private:
	Thread(const Thread& orig) { (void)orig; };
	Thread& operator=(const Thread& orig) { (void)orig; return (*this); };

private:
	Thread::Status	_status;
	pthread_t		_thread;
};

#endif	/* THREAD_HPP */
