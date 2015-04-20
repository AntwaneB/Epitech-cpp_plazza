/*
 * File:   Americana.cpp
 * Author: buchse_a
 *
 * Created on April 16, 2015, 6:53 PM
 */

#include <iostream>
#include "Americana.hpp"

APizza*	Americaine::newAmericaine(APizza::SizePizza size, double cookingTime)
{
	return (new Americaine(size, cookingTime));
}

Americaine::Americaine(APizza::SizePizza size, double cookingTime)
	: APizza(APizza::Americaine, size)
{
	_ingredients.push_back(APizza::Ingredients::Doe);
	_ingredients.push_back(APizza::Ingredients::Tomato);
	_ingredients.push_back(APizza::Ingredients::Gruyere);
	_ingredients.push_back(APizza::Ingredients::Steak);
	_cookingTime = 2.0 * cookingTime;
}

Americaine::~Americaine()
{
}
