/*
 * File:   Cook.hpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 11:28 AM
 */

#ifndef COOK_HPP
#define	COOK_HPP

#include "ITask.hpp"
#include "APizza.hpp"

class Cook : public ITask
{
public:
	Cook(APizza*);
	virtual ~Cook();

	virtual void execute(void);

private:
	APizza*	_pizza;
};

#endif	/* COOK_HPP */
