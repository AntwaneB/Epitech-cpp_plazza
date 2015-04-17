/*
 * File:   APizza.cpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 2:00 PM
 */

#include "APizza.hpp"

APizza::APizza(APizza::TypePizza type, APizza::SizePizza size)
	: _type(type), _size(size)
{

}

APizza::~APizza()
{
}

std::string APizza::pack(const APizza& pizza)
{
	(void)pizza;

	return ("");
}
