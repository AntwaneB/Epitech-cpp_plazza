/*
 * File:   Kitchen.cpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 11:02 AM
 */

#include <iostream>
#include "Kitchen.hpp"

Kitchen::Kitchen(const std::string& pathIn, const std::string& pathOut, size_t cooks, size_t resupplyTime)
	: _pathIn(pathOut), _pathOut(pathIn), _cooksCount(cooks), _resupplyTime(resupplyTime)
{
}

Kitchen::~Kitchen()
{
	if (_toReception)
		delete _toReception;
	if (_fromReception)
		delete _fromReception;
	delete _process;
}

void Kitchen::execute()
{
	_toReception = new NamedPipe::Out(_pathOut);
	_fromReception = new NamedPipe::In(_pathIn);
	std::string command;

	while ("Ceci est une boucle infinie, c'est à dire une boucle qui ne termine jamais.")
	{
		_fromReception->read(command);

		this->handleCommand(command);
	}
}

void Kitchen::handleCommand(const std::string& command)
{
	if (command == "count_available_spots")
	{
		_toReception->write(std::to_string(this->countOrdersSpots()));
	}
	else if (command.substr(0, 4) == "cook")
	{
		std::cout << "Kitchen " << getpid() << " is cooking " << command.substr(5) << std::endl;
	}
	else if (command == "die")
	{
		std::cout << "Kitchen " << getpid() << " is closing" << std::endl;
		exit(0);
	}
	else
		std::cerr << "Bad command : '" << command << "'" << std::endl;
}

size_t Kitchen::countOrdersSpots() const
{
	static size_t minus = -1;

	if (minus > _cooksCount)
		minus = 0;
	else
		minus++;

	return (_cooksCount - minus > _cooksCount ? _cooksCount : _cooksCount - minus); // TO CHANGE
}
