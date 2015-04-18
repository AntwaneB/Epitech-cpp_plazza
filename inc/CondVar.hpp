/*
 * File:   CondVar.hpp
 * Author: buchse_a
 *
 * Created on April 18, 2015, 12:20 PM
 */

#ifndef CONDVAR_HPP
#define	CONDVAR_HPP

#include <string>
#include <pthread.h>
#include "Mutex.hpp"

class CondVar
{
public:
	CondVar();
	virtual ~CondVar();

	void	wait(void);
	void	signal(void);
	void	broadcast(void);

private:
	Mutex					_mutex;
	pthread_cond_t		_condvar;
};

#endif	/* CONDVAR_HPP */
