#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Reception.hpp"
#include "NamedPipe.hpp"
#include "Margarita.hpp"
#include "StringHelper.hpp"

Reception::Reception(double cookingTime, size_t cooksCount, size_t resupplyTime)
	: _cookingTime(cookingTime), _cooksCount(cooksCount), _resupplyTime(resupplyTime)
{
	_pizzasCtor.insert(std::map<APizza::TypePizza, APizza* (*)(APizza::SizePizza, double)>::value_type(APizza::Margarita, &Margarita::newMargarita));
	_pizzaCvt["regina"] = APizza::Regina;
	_pizzaCvt["margarita"] = APizza::Margarita;
	_pizzaCvt["americaine"] = APizza::Americaine;
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

	std::stringstream sstm;
	sstm << "/tmp/buchse_a_receptionin_" << count;
	std::string kitchenPathIn = sstm.str();

	sstm.str(std::string());
	sstm << "/tmp/buchse_a_receptionout_" << count;
	std::string kitchenPathOut = sstm.str();

	new KitchenFactory(kitchenPathIn, kitchenPathOut, _cooksCount, _resupplyTime);

	std::cout << "In reception (" << getpid() << ") : ";
	NamedPipe::In*		in = new NamedPipe::In(kitchenPathIn);
	std::cout << "In reception : ";
	NamedPipe::Out*	out = new NamedPipe::Out(kitchenPathOut);

	_kitchens.push_back(std::make_pair(in, out));
	count++;

	return (_kitchens.back());
}

void	Reception::handleQueue()
{
	if (!_orders.empty() && _kitchens.empty())
		this->openKitchen();

	std::cout << "\n\n\n";
	while (!_orders.empty())
	{
		APizza* pizza = _orders.front();
		_orders.pop();

		std::map<std::pair<NamedPipe::In*, NamedPipe::Out*>, int> freeCooks;
		for (std::list<std::pair<NamedPipe::In*, NamedPipe::Out*> >::iterator kitchen = _kitchens.begin(); kitchen != _kitchens.end(); ++kitchen)
		{
			NamedPipe::Out*	toKitchen = (*kitchen).second;
			NamedPipe::In*		fromKitchen = (*kitchen).first;

			std::cout << "In reception (" << getpid() << ") : ";
			(*toKitchen) << "count_available_cooks";

			std::string cooksCount;
			std::cout << "In reception (" << getpid() << ") : ";
			(*fromKitchen) >> cooksCount;
			std::cout << std::endl << "Their's " << cooksCount << " cooks available in this kitchen !" << std::endl << std::endl;

			if (cooksCount != "kitchen_closed")
				freeCooks.insert(std::map<std::pair<NamedPipe::In*, NamedPipe::Out*>, int>::value_type(std::make_pair((*kitchen).first, (*kitchen).second), std::stoi(cooksCount)));
			else
			{
				kitchen = _kitchens.erase(kitchen);
				--kitchen;
			}
		}

		std::pair<std::pair<NamedPipe::In*, NamedPipe::Out*>, int> freeKitchen(*(std::max_element(freeCooks.begin(), freeCooks.end())));

		// Opening a new kitchen if needed
		std::cout << "In reception : ";
		NamedPipe::Out*	toKitchen = freeKitchen.second > 0 ? freeKitchen.first.second : this->openKitchen().second;
		(*toKitchen) << "cook " + APizza::pack(*pizza);
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
		// lancer une exception !!!
	}
}

void	Reception::start()
{
	std::string 				save;

	while ("Supernatural")
	{
		std::getline(std::cin, save);
		std::vector<std::string> orders = StringHelper::strtovec(save, ";");
		for (size_t i = 0; i < orders.size(); i++)
		{
			createPizza(StringHelper::strtovec(orders[i], " "));
		}
		this->handleQueue();
	}
}
