/*
 * File:   Mutex.cpp
 * Author: buchse_a
 *
 * Created on April 9, 2015, 6:00 PM
 */

#include <errno.h>
#include <string.h>
#include "Mutex.hpp"

Mutex::Mutex()
	: _mutex(new pthread_mutex_t)
{
	if (pthread_mutex_init(_mutex, NULL) != 0)
		throw Mutex::Exception(std::string("phtread_mutex_init: ") + strerror(errno));
}

Mutex::~Mutex()
{
	if (pthread_mutex_destroy(_mutex) != 0)
		throw Mutex::Exception(std::string("phtread_mutex_destroy: ") + strerror(errno));
}

void Mutex::lock()
{
	if (pthread_mutex_lock(_mutex) != 0)
		throw Mutex::Exception(std::string("phtread_mutex_lock: ") + strerror(errno));
}

void Mutex::unlock()
{
	if (pthread_mutex_unlock(_mutex) != 0)
		throw Mutex::Exception(std::string("phtread_mutex_unlock: ") + strerror(errno));
}

bool Mutex::trylock()
{
	return (pthread_mutex_trylock(_mutex) == 0);
}

pthread_mutex_t* Mutex::getMutex(void) const
{
	return (_mutex);
}