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

Reception::Reception()
{
}

Reception::~Reception()
{
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
