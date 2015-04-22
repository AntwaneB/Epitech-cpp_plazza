#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Reception.hpp"
#include "NamedPipe.hpp"
#include "Mutex.hpp"
#include "ScopedLock.hpp"
#include "Margarita.hpp"
#include "Regina.hpp"
#include "Fantasia.hpp"
#include "Americana.hpp"
#include "StringHelper.hpp"

Reception::Reception(double cookingTime, size_t cooksCount, size_t resupplyTime)
	: _cookingTime(cookingTime), _cooksCount(cooksCount), _resupplyTime(resupplyTime)
{
	_pizzasCtor.insert(std::map<APizza::TypePizza, APizza* (*)(APizza::SizePizza, double)>::value_type(APizza::Margarita, &Margarita::newMargarita));
	_pizzasCtor.insert(std::map<APizza::TypePizza, APizza* (*)(APizza::SizePizza, double)>::value_type(APizza::Regina, &Regina::newRegina));
	_pizzasCtor.insert(std::map<APizza::TypePizza, APizza* (*)(APizza::SizePizza, double)>::value_type(APizza::Americaine, &Americaine::newAmericaine));
	_pizzasCtor.insert(std::map<APizza::TypePizza, APizza* (*)(APizza::SizePizza, double)>::value_type(APizza::Fantasia, &Fantasia::newFantasia));
	_pizzaCvt["regina"] = APizza::Regina;
	_pizzaCvt["margarita"] = APizza::Margarita;
	_pizzaCvt["americana"] = APizza::Americaine;
	_pizzaCvt["fantasia"] = APizza::Fantasia;
	_sizeCvt["S"] = APizza::S;
	_sizeCvt["M"] = APizza::M;
	_sizeCvt["L"] = APizza::L;
	_sizeCvt["XL"] = APizza::XL;
	_sizeCvt["XXL"] = APizza::XXL;
}

Reception::~Reception()
{
}

std::pair<NamedPipe::In*, NamedPipe::Out*> Reception::openKitchen()
{
	static size_t	count = 0;

	Mutex mutex;
	ScopedLock	lock(mutex);

	std::stringstream sstm;
	sstm << "/tmp/buchse_a_receptionin_" << count;
	std::string kitchenPathIn = sstm.str();

	sstm.str(std::string());
	sstm << "/tmp/buchse_a_receptionout_" << count;
	std::string kitchenPathOut = sstm.str();

	new KitchenFactory(kitchenPathIn, kitchenPathOut, _cooksCount, _resupplyTime);

	Mutex mutexPipe;
	mutexPipe.lock();
	NamedPipe::In*		in = new NamedPipe::In(kitchenPathIn);
	mutexPipe.unlock();
	mutexPipe.lock();
	NamedPipe::Out*	out = new NamedPipe::Out(kitchenPathOut);
	mutexPipe.unlock();

	_kitchens.push_back(std::make_pair(in, out));
	count++;

	_guiKitchens.resize(_guiKitchens.size() + 1);

	return (_kitchens.back());
}

void	Reception::handleQueue()
{
	if (!_orders.empty() && _kitchens.empty())
		this->openKitchen();

	while (!_orders.empty())
	{
		APizza* pizza = _orders.front();
		_orders.pop();

		size_t i = 0;
		std::map<std::pair<NamedPipe::In*, NamedPipe::Out*>, int> freeCooks;
		for (std::list<std::pair<NamedPipe::In*, NamedPipe::Out*> >::iterator kitchen = _kitchens.begin(); kitchen != _kitchens.end(); ++kitchen)
		{
			NamedPipe::Out*	toKitchen = (*kitchen).second;
			NamedPipe::In*		fromKitchen = (*kitchen).first;

			(*toKitchen) << "count_available_spots";

			std::string cooksCount;
			(*fromKitchen) >> cooksCount;

			(*toKitchen) << "can_cook " + APizza::pack(*pizza);
			std::string canCook;
			(*fromKitchen) >> canCook;

			std::list<int>::iterator itGui = _guiKitchens.begin();
			std::advance(itGui, i);
			*itGui = cooksCount == "kitchen_closed" ? -1 : std::stoi(cooksCount);

			if (cooksCount != "kitchen_closed" && canCook == "true")
				freeCooks.insert(std::map<std::pair<NamedPipe::In*, NamedPipe::Out*>, int>::value_type(std::make_pair((*kitchen).first, (*kitchen).second), std::stoi(cooksCount)));
			else if (cooksCount == "kitchen_closed")
			{
				delete (*kitchen).first;
				delete (*kitchen).second;
				kitchen = _kitchens.erase(kitchen);
				--kitchen;
				_guiKitchens.erase(itGui);
				i--;
			}
			i++;
		}

		if (!_kitchens.empty() && !freeCooks.empty())
		{
			std::pair<std::pair<NamedPipe::In*, NamedPipe::Out*>, int> freeKitchen(*(std::max_element(freeCooks.begin(), freeCooks.end())));

			NamedPipe::Out*	toKitchen = freeKitchen.second > 0 ? freeKitchen.first.second : this->openKitchen().second;
			(*toKitchen) << "cook " + APizza::pack(*pizza);
		}
		else
		{
			NamedPipe::Out*	toKitchen = this->openKitchen().second;
			(*toKitchen) << "cook " + APizza::pack(*pizza);
		}
	}
}

void	Reception::createPizza(std::vector<std::string> pizza)
{
	if (!pizza.empty() && pizza.size() == 3 && _pizzaCvt.find(pizza[0]) != _pizzaCvt.end() && _sizeCvt.find(pizza[1]) != _sizeCvt.end())
	{
		pizza[2].erase(0, 1);
		int nb = std::stoi(pizza[2]);
		for (int i = 0; i < nb; i++)
		{
			_orders.push((_pizzasCtor.find(_pizzaCvt.find(pizza[0])->second)->second)(_sizeCvt.find(pizza[1])->second, _cookingTime));
		}
	}
	else if (!pizza.empty() && (pizza.size() != 3 || _pizzaCvt.find(pizza[0]) == _pizzaCvt.end() || _sizeCvt.find(pizza[1]) == _sizeCvt.end()))
	{
		std::cerr << "Invalid pizza '" << pizza[0] << "'" << std::endl;
	}
}

void	Reception::closeKitchens()
{
	for (std::list<std::pair<NamedPipe::In*, NamedPipe::Out*> >::iterator kitchen = _kitchens.begin(); kitchen != _kitchens.end(); ++kitchen)
	{
		(*((*kitchen).second)) << "die";
	}
}

void	Reception::guiListener()
{
	while (true)
	{
		std::string command;
		(*_guiPipes.first) >> command;

		if (command == "get_kitchens")
		{
			std::string result = "kitchens:";

			for (std::list<int>::const_iterator it = _guiKitchens.begin(); it != _guiKitchens.end(); ++it)
			{
				result += std::to_string(*it);
				result += " ";
			}

			(*_guiPipes.second) << result;
		}
	}
}

void	Reception::start()
{
	bool			run = true;

	NamedPipe::In*		in = new NamedPipe::In("/tmp/buchse_a_from-gui");
	NamedPipe::Out*	out = new NamedPipe::Out("/tmp/buchse_a_to-gui");
	_guiPipes.first = in;
	_guiPipes.second = out;

	Thread guiListenerThread;
	guiListenerThread.run([](void* arg) -> void* {
		Reception*	reception = static_cast<Reception*>(arg);

		reception->guiListener();

		return (NULL);
	}, this);

	while (run)
	{
		std::cout << "> " << std::flush;

		std::string save;
		std::getline(std::cin, save);
		if (save == "exit")
		{
			this->closeKitchens();
			run = false;
		}
		else
		{
			std::vector<std::string> orders = StringHelper::strtovec(save, ";");
			for (size_t i = 0; i < orders.size(); i++)
			{
				createPizza(StringHelper::strtovec(orders[i], " "));
			}
			this->handleQueue();
		}
	}
}
