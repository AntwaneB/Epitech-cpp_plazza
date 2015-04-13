/*
 * File:   APizza.hpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 2:00 PM
 */

#ifndef APIZZA_HPP
#define	APIZZA_HPP

#include <vector>

class APizza
{
public:
	enum TypePizza
	{
		Regina = 1,
		Margarita = 2,
		Americaine = 4,
		Fantasia = 8
	};

	enum SizePizza
	{
		S = 1,
		M = 2,
		L = 4,
		XL = 8,
		XXL = 16
	};

	enum Ingredients
	{
		Doe,
		Tomato,
		Gruyere,
		Ham,
		Mushrooms,
		Steak,
		Eggplant,
		GoatCheese,
		ChiefLove
	};

public:
	APizza();
	virtual ~APizza() = 0;

	APizza::TypePizza						getType(void) const;
	APizza::SizePizza						getSize(void) const;
	std::vector<APizza::Ingredients>	getIngredients(void) const;

private:
	APizza::TypePizza						_type;
	APizza::SizePizza						_size;
	std::vector<APizza::Ingredients>	_ingredients;
};

#endif	/* APIZZA_HPP */
