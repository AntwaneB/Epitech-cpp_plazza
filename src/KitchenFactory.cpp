/*
 * File:   KitchenFactory.cpp
 * Author: buchse_a
 *
 * Created on April 17, 2015, 6:31 PM
 */

#include "KitchenFactory.hpp"

KitchenFactory::KitchenFactory(const std::string& pathIn, const std::string& pathOut, size_t cooks, size_t resupplyTime)
{
	Kitchen*	tmp = new Kitchen(pathIn, pathOut, cooks, resupplyTime);
	_process = new Process(*tmp);
	delete tmp;
}

KitchenFactory::~KitchenFactory()
{
	delete _process;
}