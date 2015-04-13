/*
 ** App.cpp
 **
 ** Made by Antoine Buchser
 ** Login   <buchse_a@epitech.eu>
 **
 ** Started on February 6, 2015, 10:53 AM Antoine Buchser
 ** Updated on February 6, 2015, 10:53 AM Antoine Buchser
 */

#include <iostream>
#include <unistd.h>
#include "Exception.hpp"
#include "App.hpp"
#include "Clock.hpp"
#include "Thread.hpp"
#include "Mutex.hpp"
#include "ScopedLock.hpp"

App::App(int ac, char** av)
	: _ac(ac), _av(av)
{
	if (!this->validateArgs())
		throw ArgumentsException("usage:\n" \
										 "./plazza [cooking time] [cooks per kitchen] [resupply time]");
}

App::~App()
{
	if (this)
	{
	}
}

bool	App::validateArgs() const
{
	return (true);
}

Thread	thread1;
Thread	thread2;
Thread	threadWaiter;

void*	runThreadContent1(void* time)
{
	std::cout << "Starting thread execution" << std::endl;
	sleep(2);
	std::cout << "Middle thread execution" << std::endl;
	thread1.stop(strdup("Owned"));
	sleep(50);
	std::cout << "Ending thread execution" << std::endl;

	return (time);
}

void*	runThreadContent2(void* time)
{
	std::cout << "Starting thread execution" << std::endl;
	sleep(2);
	std::cout << "Middle thread execution" << std::endl;
	sleep(5);
	std::cout << "Ending thread execution" << std::endl;

	return (time);
}

void*	waiter(void* time)
{
	void* ret1 = thread1.wait();
	std::cout << "Retour du thread 1 : " << (char*)ret1 << std::endl;

	void* ret2 = thread2.wait();
	std::cout << "Retour du thread 2 : " << (char*)ret2 << std::endl;

	return (time);
}

int	App::run() const
{
	try
	{
		Clock	clock;

		while ("supernatural c'est trop bien")
		{
			seconds_t sec = clock.tick();
			if (sec >= 5.0)
			{
				std::cout << "5 secondes" << std::endl;
				clock.resetSec();
				exit(0);
			}
		}

	thread1.run(&runThreadContent1, strdup("Hey salut"));
	thread2.run(&runThreadContent2, strdup("Hey coucou"));
	sleep(1);
	waiter(NULL);
	} catch (std::exception const & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}
