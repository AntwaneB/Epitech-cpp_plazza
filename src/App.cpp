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

App::App(int ac, char** av)
	: _ac(ac), _av(av)
{
	if (!this->validateArgs())
		throw ArgumentsException("usage:\n" \
										 "   ./plazza [cooking time] [cooks per kitchen]");
}

App::~App()
{
	if (this)
	{
	}
}

bool	App::validateArgs() const
{
	return (true);
}

int	App::run() const
{
	return (0);
}
