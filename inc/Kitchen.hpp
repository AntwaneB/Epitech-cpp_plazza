/*
 * File:   Kitchen.hpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 11:02 AM
 */

#ifndef KITCHEN_HPP
#define	KITCHEN_HPP

class Kitchen
{
public:
	Kitchen(size_t cookingTime, size_t cooks, size_t resupplyTime);
	virtual ~Kitchen();

private:
	size_t	_cookingTime;
	size_t	_cooksCount;
	size_t	_resupplyTime;
};

#endif	/* KITCHEN_HPP */
