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
	std::cout << _pizza->getCookingTime() << std::endl;
	usleep(_pizza->getCookingTime() * 1000000);
	std::cout << "Cook is done cooking " << APizza::pack(*_pizza);
}
