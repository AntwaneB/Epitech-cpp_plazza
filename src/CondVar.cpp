/*
 * File:   CondVar.cpp
 * Author: buchse_a
 *
 * Created on April 18, 2015, 12:20 PM
 */

#include <errno.h>
#include "CondVar.hpp"

CondVar::CondVar()
{
	pthread_cond_init(&_condvar, NULL);
}

CondVar::~CondVar()
{
	pthread_cond_destroy(&_condvar);
}

void CondVar::wait()
{
	pthread_cond_wait(&_condvar, _mutex.getMutex());
}

void CondVar::signal()
{
	pthread_cond_signal(&_condvar);
}

void CondVar::broadcast()
{
	pthread_cond_broadcast(&_condvar);
}
