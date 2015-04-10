/*
 * File:   ScopedLock.cpp
 * Author: buchse_a
 *
 * Created on April 10, 2015, 2:10 PM
 */

#include "ScopedLock.hpp"

ScopedLock::ScopedLock(Mutex & mutex)
	: _mutex(mutex)
{
	_mutex.lock();
}

ScopedLock::~ScopedLock()
{
	_mutex.unlock();
}

