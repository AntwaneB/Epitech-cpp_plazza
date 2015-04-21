/*
 * File:   Regina.cpp
 * Author: buchse_a
 *
 * Created on April 16, 2015, 6:53 PM
 */

#include <iostream>
#include "Regina.hpp"

APizza*	Regina::newRegina(APizza::SizePizza size, double cookingTime)
{
	return (new Regina(size, cookingTime));
}

Regina::Regina(APizza::SizePizza size, double cookingTime)
	: APizza(APizza::Regina, size, cookingTime)
{
	_ingredients.push_back(APizza::Ingredients::Doe);
	_ingredients.push_back(APizza::Ingredients::Tomato);
	_ingredients.push_back(APizza::Ingredients::Gruyere);
	_ingredients.push_back(APizza::Ingredients::Ham);
	_ingredients.push_back(APizza::Ingredients::Mushrooms);
	_cookingTime = 2.0 * cookingTime;
}

Regina::~Regina()
{
}
