/*
 * File:   Kitchen.cpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 11:02 AM
 */

#include <iostream>
#include "Cook.hpp"
#include "Mutex.hpp"
#include "ScopedLock.hpp"
#include "Kitchen.hpp"

Kitchen::Kitchen(const std::string& pathIn, const std::string& pathOut, size_t cooks, size_t resupplyTime)
	: _pathIn(pathOut), _pathOut(pathIn), _cooksCount(cooks), _resupplyTime(resupplyTime), _dead(false)
{
	_toReception = NULL;
	_fromReception = NULL;
	_process = NULL;
	_cooks = new ThreadPool(_cooksCount);
}

Kitchen::~Kitchen()
{
	if (_toReception)
		delete _toReception;
	if (_fromReception)
		delete _fromReception;
	if (_process)
		delete _process;
}

void Kitchen::execute()
{
	Mutex			mutex;
	mutex.lock();
	_toReception = new NamedPipe::Out(_pathOut);
	mutex.unlock();
	mutex.lock();
	_fromReception = new NamedPipe::In(_pathIn);
	mutex.unlock();
	std::string command;

	Clock clock;

	while ("Ceci est une boucle infinie, c'est à dire une boucle qui ne termine jamais.")
	{
		_fromReception->read(command);

		seconds_t sec = clock.tick();
		if (sec >= 5.0)
			_dead = true;

		this->handleCommand(command, clock);
	}
}

void Kitchen::handleCommand(const std::string& command, Clock & clock)
{
	Mutex			mutex;
	ScopedLock	lock(mutex);

	if (_dead && command != "die")
	{
		std::cout << "Oh, no ! The kitchen was unused for too long !" << std::endl;
		_toReception->write("kitchen_closed");
		exit(0);
	}
	else
	{
		if (command == "count_available_spots")
		{
			_toReception->write(std::to_string(this->countOrdersSpots()));
		}
		else if (command.substr(0, 4) == "cook")
		{
			std::cout << "Pizza to cook : '" << command.substr(5) << "'" << std::endl;
			clock.resetSec();
			_cooks->pushTask(new Cook(APizza::unpack(command.substr(5))));
			_cooks->runTasks();
		}
		else if (command == "die")
		{
			std::cout << "Kitchen " << getpid() << " is closing" << std::endl;
			exit(0);
		}
		else
			std::cerr << "Bad command : '" << command << "'" << std::endl;
	}
}

size_t Kitchen::countOrdersSpots() const
{
/*
	static size_t minus = 0;

	minus++;

	return (_cooksCount - minus > _cooksCount ? 0 : _cooksCount - minus); // TO CHANGE
*/
	return (_cooks->countAvailable());
}
