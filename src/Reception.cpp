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

void	Reception::start()
{
	std::ifstream				ofs;
	std::string 				save;
	int							i;

	while ("Supernatural")
	{
		char tmp[500];
		std::cin.getline(tmp, 500, '\n');
		save = std::string(tmp);
		std::cout << "Supernatural:" << save << std::endl;
		i++;
	}
}
