/*
 * File:   Kitchen.cpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 11:02 AM
 */

#include <iostream>
#include "Cook.hpp"
#include "StringHelper.hpp"
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

size_t Kitchen::countOrdersSpots() const
{
	return (_cooks->countAvailable());
}

void Kitchen::handleCommand(std::string& command, Clock & clock)
{
	Mutex			mutex;
	ScopedLock	lock(mutex);

	std::map<std::string, bool (Kitchen::*)(const std::string&)> actions;
	actions.insert(std::map<std::string, bool (Kitchen::*)(const std::string&)>::value_type("die", &Kitchen::handleDie));
	actions.insert(std::map<std::string, bool (Kitchen::*)(const std::string&)>::value_type("dead", &Kitchen::handleDead));
	actions.insert(std::map<std::string, bool (Kitchen::*)(const std::string&)>::value_type("count_available_spots", &Kitchen::handleCount));
	actions.insert(std::map<std::string, bool (Kitchen::*)(const std::string&)>::value_type("cook", &Kitchen::handleCook));

	command = _dead ? "die" : command;
	std::vector<std::string> parts = StringHelper::strtovec(command, " ");
	if (!parts.empty() && actions.find(parts[0]) != actions.end())
	{
		if ((this->*(actions.find(parts[0])->second))(command))
			clock.resetSec();
	}
}

bool Kitchen::handleCook(const std::string& command)
{
	std::cout << "Pizza to cook : '" << command.substr(5) << "'" << std::endl;
	_cooks->pushTask(new Cook(APizza::unpack(command.substr(5))));
	_cooks->runTasks();

	return (true);
}

bool Kitchen::handleCount(const std::string& command)
{
	(void)command;

	_toReception->write(std::to_string(this->countOrdersSpots()));

	return (false);
}

bool Kitchen::handleDead(const std::string& command)
{
	(void)command;

	std::cout << "Kitchen " << getpid() << " was unused for too long !" << std::endl;
	_toReception->write("kitchen_closed");
	exit(EXIT_FAILURE);

	return (false);
}

bool Kitchen::handleDie(const std::string& command)
{
	(void)command;

	std::cout << "Kitchen " << getpid() << " is closing it's doors" << std::endl;
	exit(EXIT_SUCCESS);

	return (false);
}
