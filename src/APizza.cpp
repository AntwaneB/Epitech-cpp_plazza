/*
 * File:   APizza.cpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 2:00 PM
 */

#include <iostream>
#include "APizza.hpp"
#include "Reception.hpp"
#include "StringHelper.hpp"
#include "Margarita.hpp"
#include "Regina.hpp"
#include "Fantasia.hpp"
#include "Americana.hpp"

APizza::APizza(APizza::TypePizza type, APizza::SizePizza size, double cookingTimeModifier)
	: _type(type), _size(size), _cookingTimeModifier(cookingTimeModifier)
{

}

APizza::~APizza()
{
}

APizza::TypePizza APizza::getType(void) const
{
	return (_type);
}

APizza::SizePizza APizza::getSize(void) const
{
	return (_size);
}

std::vector<APizza::Ingredients> APizza::getIngredients(void) const
{
	return (_ingredients);
}

double APizza::getCookingTime(void) const
{
	return (_cookingTime);
}

double APizza::getModifier(void) const
{
	return (_cookingTimeModifier);
}

std::string APizza::pack(const APizza& pizza)
{
	std::map<APizza::TypePizza, std::string> TypePizzaMap =
	{
		{ APizza::Regina, "regina" },
		{ APizza::Margarita, "margarita" },
		{ APizza::Americaine, "americaine" },
		{ APizza::Fantasia, "fantasia" }
	};

	std::map<APizza::SizePizza, std::string> SizePizzaMap =
	{
		{ APizza::S, "S" },
		{ APizza::M, "M" },
		{ APizza::L, "L" },
		{ APizza::XL, "XL" },
		{ APizza::XXL, "XXL" }
	};

	return (TypePizzaMap[pizza.getType()] + " " + SizePizzaMap[pizza.getSize()] + " " + std::to_string(pizza.getModifier()));
}

APizza*	APizza::stringToAPizza(std::vector<std::string> const pizza)
{
	std::map<APizza::TypePizza, APizza* (*)(APizza::SizePizza, double)>	pizzasCtor;
	std::map<std::string, APizza::TypePizza>	pizzaCvt;
	std::map<std::string, APizza::SizePizza>	sizeCvt;

	pizzasCtor.insert(std::map<APizza::TypePizza, APizza* (*)(APizza::SizePizza, double)>::value_type(APizza::Margarita, &Margarita::newMargarita));
	pizzasCtor.insert(std::map<APizza::TypePizza, APizza* (*)(APizza::SizePizza, double)>::value_type(APizza::Regina, &Regina::newRegina));
	pizzasCtor.insert(std::map<APizza::TypePizza, APizza* (*)(APizza::SizePizza, double)>::value_type(APizza::Americaine, &Americaine::newAmericaine));
	pizzasCtor.insert(std::map<APizza::TypePizza, APizza* (*)(APizza::SizePizza, double)>::value_type(APizza::Fantasia, &Fantasia::newFantasia));
	pizzaCvt["regina"] = APizza::Regina;
	pizzaCvt["margarita"] = APizza::Margarita;
	pizzaCvt["americaine"] = APizza::Americaine;
	pizzaCvt["fantasia"] = APizza::Fantasia;
	sizeCvt["S"] = APizza::S;
	sizeCvt["M"] = APizza::M;
	sizeCvt["L"] = APizza::L;
	sizeCvt["XL"] = APizza::XL;
	sizeCvt["XXL"] = APizza::XXL;

	return ((pizzasCtor.find(pizzaCvt.find(pizza[0])->second)->second)(sizeCvt.find(pizza[1])->second, std::stoi(pizza[2])));
}

APizza*		APizza::unpack(std::string const & pizza)
{
	std::vector<std::string> order = StringHelper::strtovec(pizza, " ");

	return (stringToAPizza(order));
}