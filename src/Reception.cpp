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

std::pair<std::string, std::string> Reception::openKitchen()
{
	static size_t	count = 0;

	std::stringstream sstm;
	sstm << "/tmp/buchse_a_kitchenIn_" << count;
	std::string kitchenPathIn = sstm.str();

	sstm.str(std::string());
	sstm << "/tmp/buchse_a_kitchenOut_" << count;
	std::string kitchenPathOut = sstm.str();

	new Kitchen(kitchenPathIn, kitchenPathOut, _cooksCount, _resupplyTime);

	_kitchens.push_back(std::make_pair(kitchenPathIn, kitchenPathOut));
	count++;

	return (std::make_pair(kitchenPathIn, kitchenPathOut));
}

void	Reception::handleQueue()
{
	if (!_orders.empty() && _kitchens.empty())
		this->openKitchen();

	while (!_orders.empty())
	{
		APizza* pizza = _orders.front();
		_orders.pop();

		std::map<std::pair<std::string, std::string>, int> freeCooks;
		for (std::list<std::pair<std::string, std::string> >::iterator kitchen = _kitchens.begin(); kitchen != _kitchens.end(); ++kitchen)
		{
			NamedPipe::Out	toKitchen((*kitchen).second);
			toKitchen << "count_available_cooks\n";

			NamedPipe::In	fromKitchen((*kitchen).first);
			std::string cooksCount;
			fromKitchen >> cooksCount;

			if (cooksCount != "kitchen_closed")
				freeCooks.insert(std::map<std::pair<std::string, std::string>, int>::value_type(std::make_pair((*kitchen).first, (*kitchen).second), std::stoi(cooksCount)));
			else
			{
				kitchen = _kitchens.erase(kitchen);
				--kitchen;
			}
		}

		std::pair<std::pair<std::string, std::string>, int> freeKitchen(*(std::max_element(freeCooks.begin(), freeCooks.end())));
		std::cout << freeKitchen.first.first << std::endl;

		// Opening a new kitchen if needed
		NamedPipe::Out	toKitchen(freeKitchen.second > 0 ? freeKitchen.first.second : this->openKitchen().second);
		toKitchen << "cook " << APizza::pack(*pizza);
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
