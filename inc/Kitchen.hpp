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
#include "NamedPipe.hpp"
#include "APizza.hpp"

class Kitchen : public ITask
{
public:
	Kitchen(std::string const & pathIn, std::string const & pathOut, size_t cooks, size_t resupplyTime);
	virtual ~Kitchen();

	virtual void	execute(void);

private:
	bool	canCook(APizza*);
	void	cook(APizza*);

	void	handleCommand(std::string const &);

private:
	Process*				_process;
	NamedPipe::In*		_fromReception;
	NamedPipe::Out*	_toReception;

	size_t				_cooksCount;
	size_t				_resupplyTime;

	std::queue<APizza*>							_orders;
	std::map<APizza::Ingredients, size_t>	_supplies;
};

#endif	/* KITCHEN_HPP */
