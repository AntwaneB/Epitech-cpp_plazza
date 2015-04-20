/*
 * File:   Mutex.hpp
 * Author: buchse_a
 *
 * Created on April 9, 2015, 6:00 PM
 */

#ifndef MUTEX_HPP
#define	MUTEX_HPP

class Mutex;

#include <string>
#include <stdexcept>
#include <pthread.h>

class Mutex
{
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
	enum Status { LOCKED, UNLOCKED };

public:
	Mutex();
	virtual ~Mutex();

	virtual void	lock(void);
	virtual void	unlock(void);
	virtual bool	trylock(void);

	pthread_mutex_t*	getMutex(void) const;

private:
	Mutex(const Mutex& orig){ (void)orig; };
	Mutex& operator=(const Mutex& orig){ (void)orig; return (*this); };

private:
	pthread_mutex_t*	_mutex;
	Mutex::Status		_status;
};

#endif	/* MUTEX_HPP */
