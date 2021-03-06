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

Reception::Reception(double cookingTime, size_t cooksCount, size_t resupplyTime, bool gui)
	: _cookingTime(cookingTime), _cooksCount(cooksCount), _resupplyTime(resupplyTime), _gui(gui)
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
	Mutex	globalMutex;
	ScopedLock	globalLock(globalMutex);

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
			if (_gui)
			{
				std::advance(itGui, i);
				*itGui = cooksCount == "kitchen_closed" ? -1 : std::stoi(cooksCount);
			}

			if (cooksCount != "kitchen_closed" && canCook == "true")
				freeCooks.insert(std::map<std::pair<NamedPipe::In*, NamedPipe::Out*>, int>::value_type(std::make_pair((*kitchen).first, (*kitchen).second), std::stoi(cooksCount)));
			else if (cooksCount == "kitchen_closed")
			{
				(*toKitchen) << "die";

				delete (*kitchen).first;
				delete (*kitchen).second;
				kitchen = _kitchens.erase(kitchen);
				--kitchen;
				if (_gui)
				{
					_guiKitchens.erase(itGui);
					i--;
				}
			}
			i++;
		}

		if (!_kitchens.empty() && !freeCooks.empty())
		{
			std::pair<std::pair<NamedPipe::In*, NamedPipe::Out*>, int> freeKitchen(*(std::max_element(freeCooks.begin(), freeCooks.end())));

			// Updating GUI count
			size_t i = 0; bool found = false;
			if (_gui)
			{
				for (std::list<std::pair<NamedPipe::In*, NamedPipe::Out*> >::iterator kitchen = _kitchens.begin(); kitchen != _kitchens.end() && !found; ++kitchen)
					if ((*kitchen).second == freeKitchen.first.second)
						found = true;
					else
						i++;
			}

			NamedPipe::Out*	toKitchen = freeKitchen.second > 0 ? freeKitchen.first.second : this->openKitchen().second;
			(*toKitchen) << "cook " + APizza::pack(*pizza);

			// Updating GUI count
			if (_gui)
			{
				std::list<int>::iterator itGui = _guiKitchens.begin();
				if (found)
				{
					std::advance(itGui, i);
					*itGui -= 1;
				}
				else
				{
					std::advance(itGui, _guiKitchens.size() - 1);
					*itGui = _cooksCount - 1;
				}
			}
		}
		else
		{
			NamedPipe::Out*	toKitchen = this->openKitchen().second;
			(*toKitchen) << "cook " + APizza::pack(*pizza);

			// Updating GUI count
			if (_gui)
			{
				std::list<int>::iterator itGui = _guiKitchens.begin();
				std::advance(itGui, _guiKitchens.size() - 1);
				*itGui = _cooksCount - 1;
			}
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
	std::string command;

	while (true)
	{
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
		else if (command.substr(0, 5) == "order")
		{
			std::vector<std::string> orders = StringHelper::strtovec(command.substr(6), ";");
			for (size_t i = 0; i < orders.size(); i++)
			{
				createPizza(StringHelper::strtovec(orders[i], " \t"));
			}
			this->handleQueue();
		}
	}
}

void	Reception::start()
{
	bool			run = true;

	if (_gui)
	{
		NamedPipe::In*		in = new NamedPipe::In("/tmp/buchse_a_from-gui");
		NamedPipe::Out*	out = new NamedPipe::Out("/tmp/buchse_a_to-gui");
		_guiPipes.first = in;
		_guiPipes.second = out;

		Thread* guiListenerThread = new Thread;
		guiListenerThread->run([](void* arg) -> void* {
			Reception*	reception = static_cast<Reception*>(arg);

			reception->guiListener();

			return (NULL);
		}, this);
	}

	std::cout << "\033[1m\033[37mHey, welcome to \033[31mThe\033[0m \033[32mPlazza\033[0m !\033[0m" << std::endl << std::endl;
	while (run)
	{
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
				createPizza(StringHelper::strtovec(orders[i], " \t"));
			}
			this->handleQueue();
		}
	}
}
