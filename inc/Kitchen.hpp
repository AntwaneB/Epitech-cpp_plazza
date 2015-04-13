/*
 * File:   Kitchen.hpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 11:02 AM
 */

#ifndef KITCHEN_HPP
#define	KITCHEN_HPP

class Reception;
class Kitchen;

#include <map>
#include <queue>
#include "Reception.hpp"
#include "APizza.hpp"

class Kitchen
{
public:
	Kitchen(size_t cookingTime, size_t cooks, size_t resupplyTime);
	virtual ~Kitchen();

	bool	canCook(APizza*);
	void	cook(APizza*);

private:
	Reception*	_reception;

	size_t	_cookingTime;
	size_t	_cooksCount;
	size_t	_resupplyTime;

	std::queue<APizza*>							_orders;
	std::map<APizza::Ingredients, size_t>	_supplies;
};

#endif	/* KITCHEN_HPP */
