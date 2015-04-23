/*
 * File:   Cook.cpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 11:28 AM
 */

#include <iostream>
#include "unistd.h"
#include "Cook.hpp"

Cook::Cook(APizza* pizza)
	: _pizza(pizza)
{
}

Cook::~Cook()
{
}

void Cook::execute()
{
	usleep(_pizza->getCookingTime() * 1000000);
	std::cout << "\033[1m\033[37m[Kitchen " << getpid() << "]\033[0m \033[32mPizza cooked : " << _pizza->toString() << "\033[0m" << std::endl;
}
