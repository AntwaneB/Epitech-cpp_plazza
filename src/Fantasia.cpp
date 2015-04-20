/*
 * File:   Fantasia.cpp
 * Author: buchse_a
 *
 * Created on April 16, 2015, 6:53 PM
 */

#include <iostream>
#include "Fantasia.hpp"

APizza*	Fantasia::newFantasia(APizza::SizePizza size, double cookingTime)
{
	return (new Fantasia(size, cookingTime));
}

Fantasia::Fantasia(APizza::SizePizza size, double cookingTime)
	: APizza(APizza::Fantasia, size)
{
	_ingredients.push_back(APizza::Ingredients::Doe);
	_ingredients.push_back(APizza::Ingredients::Tomato);
	_ingredients.push_back(APizza::Ingredients::Eggplant);
	_ingredients.push_back(APizza::Ingredients::GoatCheese);
	_ingredients.push_back(APizza::Ingredients::ChiefLove);
	_cookingTime = 4.0 * cookingTime;
}

Fantasia::~Fantasia()
{
}
