/*
 * File:   Kitchen.cpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 11:02 AM
 */

#include <iostream>
#include <algorithm>
#include <unistd.h>
#include "Cook.hpp"
#include "StringHelper.hpp"
#include "Mutex.hpp"
#include "ScopedLock.hpp"
#include "Kitchen.hpp"

Kitchen::Kitchen(const std::string& pathIn, const std::string& pathOut, size_t cooks, size_t resupplyTime)
	: _pathIn(pathOut), _pathOut(pathIn), _cooksCount(cooks), _resupplyTime(resupplyTime), _dead(false), _lifeTime(5)
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
	std::map<APizza::Ingredients, std::string> ingredientsStr =
	{
		{ APizza::Ingredients::Doe, "Doe" },
		{ APizza::Ingredients::Tomato, "Tomato" },
		{ APizza::Ingredients::Gruyere, "Gruyere" },
		{ APizza::Ingredients::Ham, "Ham" },
		{ APizza::Ingredients::Mushrooms, "Mushrooms" },
		{ APizza::Ingredients::Steak, "Steak" },
		{ APizza::Ingredients::Eggplant, "Eggplant" },
		{ APizza::Ingredients::GoatCheese, "Goat cheese" },
		{ APizza::Ingredients::ChiefLove, "Chief love" }
	};

	while (!_dead)
	{
		usleep(_resupplyTime * 1000);

		if (!_dead)
		{
			Mutex mutex;
			mutex.lock();

			for (std::map<APizza::Ingredients, int>::iterator it = _supplies.begin(); it != _supplies.end(); ++it)
				it->second += 1;

			std::string ingredients = "";
			for (std::map<APizza::Ingredients, int>::iterator it = _supplies.begin(); it != _supplies.end(); ++it)
			{
				ingredients += std::to_string(it->second);
				ingredients += " ";
				ingredients += ingredientsStr[it->first];
				ingredients += ", ";
			}
			std::cout << "\033[1m\033[37m[Kitchen " << getpid() << "]\033[0m Resupplying stock : { " << ingredients.substr(0, ingredients.size() - 2) << " }" << std::endl;
			mutex.unlock();
		}
	}
}

void Kitchen::checkActivity()
{
	_lifeClock.resetSec();

	while (!_dead)
	{
		seconds_t sec = _lifeClock.tick();
		if (sec >= _lifeTime)
		{
			_dead = true;
			std::cout << "\033[1m\033[37m[Kitchen " << getpid() << "]\033[0m \033[31mThis kitchen was inactive for too long !\033[0m" << std::endl;
		}
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

	Thread	lifeThread;
	lifeThread.run([](void* arg) -> void* {
		Kitchen* kitchen = static_cast<Kitchen*>(arg);
		kitchen->checkActivity();
		return (NULL);
	}, this);

	std::string command;
	while (true)
	{
		_fromReception->read(command);
		this->handleCommand(command);
	}
}

size_t Kitchen::countOrdersSpots() const
{
	return (_cooks->countAvailable());
}

void Kitchen::handleCommand(std::string& command)
{
	Mutex			mutex;
	ScopedLock	lock(mutex);

	std::map<std::string, bool (Kitchen::*)(const std::string&)> actions;
	actions.insert(std::map<std::string, bool (Kitchen::*)(const std::string&)>::value_type("die", &Kitchen::handleDie));
	actions.insert(std::map<std::string, bool (Kitchen::*)(const std::string&)>::value_type("dead", &Kitchen::handleDead));
	actions.insert(std::map<std::string, bool (Kitchen::*)(const std::string&)>::value_type("count_available_spots", &Kitchen::handleCount));
	actions.insert(std::map<std::string, bool (Kitchen::*)(const std::string&)>::value_type("cook", &Kitchen::handleCook));
	actions.insert(std::map<std::string, bool (Kitchen::*)(const std::string&)>::value_type("can_cook", &Kitchen::handleCanCook));

	command = command != "die" && _dead ? "dead" : command;
	std::vector<std::string> parts = StringHelper::strtovec(command, " ");
	if (!parts.empty() && actions.find(parts[0]) != actions.end())
	{
		if ((this->*(actions.find(parts[0])->second))(command))
			_lifeClock.resetSec();
	}
}

bool Kitchen::handleCanCook(const std::string& command)
{
	Mutex			mutex;
	ScopedLock	lock(mutex);

	APizza*	pizza = APizza::unpack(command.substr(9));
	_lifeTime = pizza->getCookingTime() + 5.0 > _lifeTime ? pizza->getCookingTime() + 5.0 : _lifeTime;
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

	std::cout << "\033[1m\033[37m[Kitchen " << getpid() << "]\033[0m Order received : " << pizza->toString() << std::endl;
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

	std::cout << "\033[1m\033[37m[Kitchen " << getpid() << "]\033[0m This kitchen is closing it's doors, due to it's inactivity" << std::endl;
	_toReception->write("kitchen_closed");

	return (false);
}

bool Kitchen::handleDie(const std::string& command)
{
	(void)command;

	std::cout << "\033[1m\033[37m[Kitchen " << getpid() << "]\033[0m This kitchen is closing it's doors" << std::endl;
	_toReception->write("kitchen_closed");
	exit(EXIT_SUCCESS);

	return (false);
}
