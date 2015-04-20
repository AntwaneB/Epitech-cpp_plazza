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
#include "Reception.hpp"

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
	if (_ac != 4 || atoi(_av[1]) < 0 || atoi(_av[2]) < 0 || atoi(_av[3]) < 0)
		return (false);
	return (true);
}

int	App::run() const
{
	try
	{
		Reception	reception(atof(_av[1]), atoi(_av[2]), atoi(_av[3]));

		reception.start();
	} catch (std::exception const & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}
