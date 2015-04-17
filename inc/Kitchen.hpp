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
#include "ITask.hpp"
#include "Process.hpp"
#include "Reception.hpp"
#include "APizza.hpp"

class Kitchen : public ITask
{
public:
	Kitchen(std::string const & path, size_t cooks, size_t resupplyTime);
	virtual ~Kitchen();

	virtual void	execute(void);

private:
	bool	canCook(APizza*);
	void	cook(APizza*);

private:
	std::string	_path;

	size_t		_cooksCount;
	size_t		_resupplyTime;

	std::queue<APizza*>							_orders;
	std::map<APizza::Ingredients, size_t>	_supplies;
};

#endif	/* KITCHEN_HPP */
