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
	std::cout << "In kitchen (" << getpid() << ") : ";
	_toReception = new NamedPipe::Out(_pathOut);
	std::cout << "In kitchen : ";
	_fromReception = new NamedPipe::In(_pathIn);
	std::string command;

	while ("Ceci est une boucle infinie, c'est à dire une boucle qui ne termine jamais.")
	{
		std::cout << "In kitchen : " << std::endl;
		_fromReception->read(command);

		this->handleCommand(command);
	}
}

void Kitchen::handleCommand(const std::string& command)
{
	if (command == "count_available_cooks")
	{
		std::cout << "Sending available cooks count to reception" << std::endl;
		std::cout << "In kitchen : ";
		_toReception->write("1");
	}
	else if (command.substr(0, 4) == "cook")
	{
		std::cout << "Kitchen is cooking " << command.substr(5) << std::endl;
	}
	else
		std::cerr << "Bad command" << std::endl;
}