/*
 * File:   Reception.hpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 10:59 AM
 */

#ifndef RECEPTION_HPP
#define	RECEPTION_HPP

class Reception;

#include <list>
#include "Kitchen.hpp"

class Reception
{
public:
	Reception();
	virtual ~Reception();

private:
	size_t	_cookingTime;
	size_t	_cooksCount;
	size_t	_resupplyTime;

	std::list<Kitchen*>	_kitchens;
};

#endif	/* RECEPTION_HPP */
