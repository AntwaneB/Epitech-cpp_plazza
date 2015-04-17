/*
 * File:   Reception.cpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 10:59 AM
 */

#include <iostream>
#include <fstream>
#include <string>
#include "Reception.hpp"

Reception::Reception(double cookingTime, size_t cooksCount, size_t resupplyTime)
	: _cookingTime(cookingTime), _cooksCount(cooksCount), _resupplyTime(resupplyTime)
{
	_pizzasCtor.insert(std::map<APizza::TypePizza, APizza* (*)(APizza::SizePizza)>::value_type("Margarita", &Margarita::newMargarita));
	_pizzaCvt["Regina"] = APizza::Regina;
	_pizzaCvt["Margarita"] = APizza::Margarita;
	_pizzaCvt["Americaine"] = APizza::Americaine;
	_pizzaCvt["Fantasia"] = APizza::Fantasia;
	_sizeCvt["S"] = APizza::S;
	_sizeCvt["M"] = APizza::M;
	_sizeCvt["L"] = APizza::L;
	_sizeCvt["XL"] = APizza::XL;
	_sizeCvt["XXL"] = APizza::XXL;
}

Reception::~Reception()
{
}

void	Reception::handleQueue()
{
	while (!_orders.empty())
	{
		APizza* pizza = _orders.front();
		_orders.pop();

		

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
	if (!pizza.empty() && _pizzaCvt.find(pizza[0]) != _pizzaCvt.end())
		(this->*(_pizzaCvt.find(pizza[0]))(Margarita::newMargarita(, _cookingTime));
	else if (!parts.empty() && operations.find(parts[0]) == operations.end())
	{
		std::cout << "Pizza '" << pizza[0] << "' does not exist." << std::endl;
		// lancer une exception !!!
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
