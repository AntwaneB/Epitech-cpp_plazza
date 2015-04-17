/*
 * File:   Kitchen.cpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 11:02 AM
 */

#include "Kitchen.hpp"

Kitchen::Kitchen(const std::string& path, size_t cooks, size_t resupplyTime)
	: _path(path), _cooksCount(cooks), _resupplyTime(resupplyTime)
{
	new Process(*this);
}

Kitchen::~Kitchen()
{
}

void Kitchen::execute()
{

}
