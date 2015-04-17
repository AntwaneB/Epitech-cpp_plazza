/*
 * File:   KitchenFactory.hpp
 * Author: buchse_a
 *
 * Created on April 17, 2015, 6:31 PM
 */

#ifndef KITCHENFACTORY_HPP
#define	KITCHENFACTORY_HPP

#include <map>
#include <queue>
#include "ITask.hpp"
#include "Process.hpp"
#include "Reception.hpp"
#include "NamedPipe.hpp"
#include "Kitchen.hpp"
#include "APizza.hpp"

class KitchenFactory
{
public:
	KitchenFactory(std::string const & pathIn, std::string const & pathOut, size_t cooks, size_t resupplyTime);
	virtual ~KitchenFactory();

private:
	Process*				_process;
};

#endif	/* KITCHENFACTORY_HPP */
