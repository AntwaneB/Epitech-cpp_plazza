/*
 * File:   Kitchen.cpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 11:02 AM
 */

#include <iostream>
#include "Kitchen.hpp"

Kitchen::Kitchen(const std::string& pathIn, const std::string& pathOut, size_t cooks, size_t resupplyTime)
	: _cooksCount(cooks), _resupplyTime(resupplyTime)
{
	_process = new Process(*this);
	_fromReception = new NamedPipe::In(pathIn);
	_toReception = new NamedPipe::Out(pathOut);
}

Kitchen::~Kitchen()
{
	delete _toReception;
	delete _fromReception;
	delete _process;
}

void Kitchen::execute()
{
	while ("Ceci est une boucle infinie, c'est à dire une boucle qui ne termine jamais.")
	{
		std::string command;
		_fromReception->read(command);

		this->handleCommand(command);
	}
}

void Kitchen::handleCommand(const std::string& command)
{
	if (command == "count_available_cooks")
	{
		std::cout << "Sending available cooks count to reception" << std::endl;
		_toReception->write("1\n");
	}
	else if (command.substr(0, 4) == "cook")
	{
		std::cout << "Kitchen is cooking " << command.substr(5) << std::endl;
	}
}