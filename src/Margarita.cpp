/*
 * File:   Margarita.cpp
 * Author: buchse_a
 *
 * Created on April 16, 2015, 6:53 PM
 */

#include "Margarita.hpp"


Margarita*	Margarita::newMargarita(APizza::SizePizza size)
{
	return (new Margarita(size));
}

Margarita::Margarita(APizza::SizePizza size)
	: APizza(APizza::Margarita, size)
{
	_ingredients.push_back(APizza::Ingredients::Doe);
	_ingredients.push_back(APizza::Ingredients::Tomato);
	_ingredients.push_back(APizza::Ingredients::Gruyere);
	_cookingTime = 1;
}

Margarita::~Margarita()
{
}
