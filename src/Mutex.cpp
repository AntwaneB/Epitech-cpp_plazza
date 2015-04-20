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
	: _mutex(new pthread_mutex_t), _status(Mutex::UNLOCKED)
{
	if (pthread_mutex_init(_mutex, NULL) != 0)
		throw Mutex::Exception(std::string("phtread_mutex_init: ") + strerror(errno));
}

Mutex::~Mutex()
{
	if (_status == Mutex::LOCKED)
		this->unlock();
	if (pthread_mutex_destroy(_mutex) != 0)
		throw Mutex::Exception(std::string("phtread_mutex_destroy: ") + strerror(errno));
}

void Mutex::lock()
{
	if (pthread_mutex_lock(_mutex) != 0)
		throw Mutex::Exception(std::string("phtread_mutex_lock: ") + strerror(errno));
	_status = Mutex::LOCKED;
}

void Mutex::unlock()
{
	if (pthread_mutex_unlock(_mutex) != 0)
		throw Mutex::Exception(std::string("phtread_mutex_unlock: ") + strerror(errno));
	_status = Mutex::UNLOCKED;
}

bool Mutex::trylock()
{
	bool locked = pthread_mutex_trylock(_mutex) == 0;

	_status = locked ? Mutex::LOCKED : Mutex::UNLOCKED;
	return (locked);
}

pthread_mutex_t* Mutex::getMutex(void) const
{
	return (_mutex);
}