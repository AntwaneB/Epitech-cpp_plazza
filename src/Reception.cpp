/*
 * File:   Reception.cpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 10:59 AM
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <utility>
#include "Reception.hpp"
#include "NamedPipe.hpp"

Reception::Reception(double cookingTime, size_t cooksCount, size_t resupplyTime)
	: _cookingTime(cookingTime), _cooksCount(cooksCount), _resupplyTime(resupplyTime)
{

}

Reception::~Reception()
{
}

std::string Reception::openKitchen()
{
	size_t	count = 0;

	std::stringstream sstm;
	sstm << "/tmp/buchse_a_kitchen_" << count;
	std::string kitchenPath = sstm.str();

	new Kitchen(kitchenPath, _cooksCount, _resupplyTime);
	_kitchens.push_back(kitchenPath);
	count++;

	return (kitchenPath);
}

void	Reception::handleQueue()
{
	if (!_orders.empty() && _kitchens.empty())
		this->openKitchen();

	while (!_orders.empty())
	{
		APizza* pizza = _orders.front();
		_orders.pop();

		std::map<std::string, int> freeCooks;
		for (std::list<std::string>::iterator kitchen = _kitchens.begin(); kitchen != _kitchens.end(); ++kitchen)
		{
			NamedPipe::Out	toKitchen(*kitchen);
			NamedPipe::In	fromKitchen(*kitchen);

			std::string cooksCount;
			toKitchen << "count_available_cooks";
			fromKitchen >> cooksCount;
			if (cooksCount != "kitchen_closed")
				freeCooks.insert(std::map<std::string, int>::value_type(*kitchen, std::stoi(cooksCount)));
			else
			{
				kitchen = _kitchens.erase(kitchen);
				--kitchen;
			}
		}

		std::pair<std::string, int> freeKitchen(*(std::max_element(freeCooks.begin(), freeCooks.end())));
		std::cout << freeKitchen.first << std::endl;

		// Opening a new kitchen if needed
		NamedPipe::Out	toKitchen(freeKitchen.second > 0 ? freeKitchen.first : this->openKitchen());
		toKitchen << "cook " << APizza::pack(*pizza);
	}
}

bool	Reception::inStr(char const c, std::string const & str)
{
	for (size_t i = 0; i < str.size(); i++)
		if (str[i] == c)
			return (true);
	return (false);
}

std::vector<std::string>		Reception::strtovec(std::string const & str, std::string const & delim)
{
	std::vector<std::string>	res;

	std::string	tmp = "";
	size_t		len = str.size();
	for (size_t i = 0; i < len; i++)
	{
		if (inStr(str[i], delim))
		{
			if (!tmp.empty())
			res.push_back(tmp);
			tmp.clear();
		}
		else
			tmp += str[i];
	}
	if (!tmp.empty())
		res.push_back(tmp);

	return (res);
}

void	Reception::createPizza(std::vector<std::string> pizza)
{
	for (size_t i = 0; i < pizza.size(); i++)
		{
			std::cout << pizza[i] << std::endl;
		}
}

void	Reception::start()
{
	std::string 				save;

	while ("Supernatural")
	{
		std::getline(std::cin, save);
		std::cout << "Supernatural:" << save << std::endl;
		std::vector<std::string> orders = strtovec(save, ";");
		for (size_t i = 0; i < orders.size(); i++)
		{
			createPizza(strtovec(orders[i], " "));
		}
	}
}
