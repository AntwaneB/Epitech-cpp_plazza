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
#include <queue>
#include "Kitchen.hpp"
#include "APizza.hpp"

class Reception
{
public:
	Reception(size_t cookingTime, size_t cooksCount, size_t resupplyTime);
	virtual ~Reception();

	void	start(void);

private:
	void	handleQueue(void);

private:
	size_t	_cookingTime;
	size_t	_cooksCount;
	size_t	_resupplyTime;

	std::list<Kitchen*>	_kitchens;
	std::queue<APizza*>	_orders;
};

#endif	/* RECEPTION_HPP */