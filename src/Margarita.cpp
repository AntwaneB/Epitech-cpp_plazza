/*
 * File:   Margarita.cpp
 * Author: buchse_a
 *
 * Created on April 16, 2015, 6:53 PM
 */

#include "Margarita.hpp"


APizza*	Margarita::newMargarita(APizza::SizePizza size, double cookingTime)
{
	return (new Margarita(size, cookingTime));
}

Margarita::Margarita(APizza::SizePizza size, double cookingTime)
	: APizza(APizza::Margarita, size)
{
	_ingredients.push_back(APizza::Ingredients::Doe);
	_ingredients.push_back(APizza::Ingredients::Tomato);
	_ingredients.push_back(APizza::Ingredients::Gruyere);
	_cookingTime = 1 * cookingTime;
}

Margarita::~Margarita()
{
}
