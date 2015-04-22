/*
 * File:   Kitchen.cpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 11:02 AM
 */

#include <iostream>
#include <algorithm>
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

	_supplies =
	{
		{ APizza::Ingredients::Doe, 5 },
		{ APizza::Ingredients::Tomato, 5 },
		{ APizza::Ingredients::Gruyere, 5 },
		{ APizza::Ingredients::Ham, 5 },
		{ APizza::Ingredients::Mushrooms, 5 },
		{ APizza::Ingredients::Steak, 5 },
		{ APizza::Ingredients::Eggplant, 5 },
		{ APizza::Ingredients::GoatCheese, 5 },
		{ APizza::Ingredients::ChiefLove, 5 }
	};
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

void Kitchen::refillSupplies()
{
	while (true)
	{
		sleep(5);

		Mutex mutex;
		mutex.lock();

		for (std::map<APizza::Ingredients, int>::iterator it = _supplies.begin(); it != _supplies.end(); ++it)
			it->second += 1;
		std::cout << "Refilling supplies" << std::endl;
		mutex.unlock();
	}
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

	Thread	suppliesThread;
	suppliesThread.run([](void* arg) -> void* {
		Kitchen* kitchen = static_cast<Kitchen*>(arg);

		kitchen->refillSupplies();

		return (NULL);
	}, this);

	Clock clock;

	std::string command;
	while (true)
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
	actions.insert(std::map<std::string, bool (Kitchen::*)(const std::string&)>::value_type("can_cook", &Kitchen::handleCanCook));

	command = _dead ? "die" : command;
	std::vector<std::string> parts = StringHelper::strtovec(command, " ");
	if (!parts.empty() && actions.find(parts[0]) != actions.end())
	{
		if ((this->*(actions.find(parts[0])->second))(command))
			clock.resetSec();
	}
}

bool Kitchen::handleCanCook(const std::string& command)
{
	Mutex			mutex;
	ScopedLock	lock(mutex);

	APizza*	pizza = APizza::unpack(command.substr(9));
	std::vector<APizza::Ingredients> ingredients = pizza->getIngredients();
	std::map<APizza::Ingredients, int> tmpSupplies = _supplies;

	bool canCook = true;
	for (std::vector<APizza::Ingredients>::const_iterator ingredient = ingredients.begin(); ingredient != ingredients.end() && canCook; ++ingredient)
	{
		tmpSupplies.find(*ingredient)->second--;
		if (tmpSupplies.find(*ingredient)->second < 0)
			canCook = false;
	}

	_toReception->write(canCook ? "true" : "false");

	return (false);
}

bool Kitchen::handleCook(const std::string& command)
{
	Mutex			mutex;
	ScopedLock	lock(mutex);

	APizza*	pizza = APizza::unpack(command.substr(5));
	std::vector<APizza::Ingredients> ingredients = pizza->getIngredients();

	for (std::vector<APizza::Ingredients>::const_iterator ingredient = ingredients.begin(); ingredient != ingredients.end(); ++ingredient)
	{
		_supplies.find(*ingredient)->second--;
	}

	std::cout << "Pizza to cook : '" << command.substr(5) << "'" << std::endl;
	_cooks->pushTask(new Cook(pizza));
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
