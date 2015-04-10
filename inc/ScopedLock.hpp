/*
 * File:   ScopedLock.hpp
 * Author: buchse_a
 *
 * Created on April 10, 2015, 2:10 PM
 */

#ifndef SCOPEDLOCK_HPP
#define	SCOPEDLOCK_HPP

class ScopedLock;

#include "Mutex.hpp"

class ScopedLock
{
public:
	ScopedLock(Mutex &mutex);
	virtual ~ScopedLock();

private:
	ScopedLock(const ScopedLock& orig) : _mutex(orig._mutex) { (void)orig; }
	ScopedLock& operator=(const ScopedLock& orig) { (void)orig; return (*this); }

private:
	Mutex&	_mutex;
};

#endif	/* SCOPEDLOCK_HPP */
