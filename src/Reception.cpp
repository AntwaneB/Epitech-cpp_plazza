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
	Mutex mutex;
	ScopedLock	lock(mutex);
	static size_t	count = 0;

	std::stringstream sstm;
	sstm << "/tmp/buchse_a_receptionin_" << count;
	std::string kitchenPathIn = sstm.str();

	sstm.str(std::string());
	sstm << "/tmp/buchse_a_receptionout_" << count;
	std::string kitchenPathOut = sstm.str();

	new KitchenFactory(kitchenPathIn, kitchenPathOut, _cooksCount, _resupplyTime);

	NamedPipe::In*		in = new NamedPipe::In(kitchenPathIn);
	NamedPipe::Out*	out = new NamedPipe::Out(kitchenPathOut);

	_kitchens.push_back(std::make_pair(in, out));
	count++;

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

		int i = 1;
		std::map<std::pair<NamedPipe::In*, NamedPipe::Out*>, int> freeCooks;
		for (std::list<std::pair<NamedPipe::In*, NamedPipe::Out*> >::iterator kitchen = _kitchens.begin(); kitchen != _kitchens.end(); ++kitchen)
		{
			i++;
			NamedPipe::Out*	toKitchen = (*kitchen).second;
			NamedPipe::In*		fromKitchen = (*kitchen).first;

			(*toKitchen) << "count_available_spots";

			std::string cooksCount;
			(*fromKitchen) >> cooksCount;
//			std::cout << std::endl << "Their's '" << cooksCount << "' cooks available in this kitchen !" << std::endl << std::endl;

			if (cooksCount != "kitchen_closed")
				freeCooks.insert(std::map<std::pair<NamedPipe::In*, NamedPipe::Out*>, int>::value_type(std::make_pair((*kitchen).first, (*kitchen).second), std::stoi(cooksCount)));
			else
			{
				std::cout << "Erasing kitchen from list" << std::endl;
				delete (*kitchen).first;
				delete (*kitchen).second;
				kitchen = _kitchens.erase(kitchen);
				--kitchen;
			}
		}

		if (!_kitchens.empty())
		{
			std::pair<std::pair<NamedPipe::In*, NamedPipe::Out*>, int> freeKitchen(*(std::max_element(freeCooks.begin(), freeCooks.end())));

			// Opening a new kitchen if needed
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

void	Reception::start()
{
	bool			run = true;

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
