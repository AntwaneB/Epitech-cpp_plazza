/*
 ** App.cpp
 **
 ** Made by Antoine Buchser
 ** Login   <buchse_a@epitech.eu>
 **
 ** Started on February 6, 2015, 10:53 AM Antoine Buchser
 ** Updated on February 6, 2015, 10:53 AM Antoine Buchser
 */

#include <iostream>
#include <unistd.h>
#include "Exception.hpp"
#include "App.hpp"
#include "Thread.hpp"
#include "Reception.hpp"
#include "StringHelper.hpp"
#include "GUI.hpp"
#include "Process.hpp"

App::App(int ac, char** av)
	: _ac(ac), _av(av), _gui(false)
{
	if (_ac == 5 && std::string(_av[4]) == "--gui")
	{
		_ac = 4;
		_gui = true;
	}
	if (!this->validateArgs())
		throw ArgumentsException("usage:\n" \
										 "./plazza [cooking time] [cooks per kitchen] [resupply time]");
}

App::~App()
{
	if (this)
	{
	}
}

bool	App::validateArgs() const
{
	if (_ac != 4 || atoi(_av[1]) < 0 || atoi(_av[2]) < 0 || atoi(_av[3]) < 0 ||
		!StringHelper::isDigitalString(_av[1]) || !StringHelper::isDigitalString(_av[2]) || !StringHelper::isDigitalString(_av[3]))
		return (false);
	return (true);
}

int	App::run()
{
	try
	{
		GUI*		gui;
		Process*	guiProcess;
		if (_gui)
		{
			gui = new GUI(atoi(_av[2]));
			guiProcess = new Process(*gui);
		}

		Reception	reception(atof(_av[1]), atoi(_av[2]), atoi(_av[3]), _gui);

		reception.start();

		if (_gui)
			guiProcess->wait();
	}
	catch (std::exception const & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}
