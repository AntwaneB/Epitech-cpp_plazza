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
#include "Clock.hpp"
#include "ThreadPool.hpp"
#include "APizza.hpp"

class Kitchen : public ITask
{
public:
	Kitchen(std::string const & pathIn, std::string const & pathOut, size_t cooks, size_t resupplyTime);
	virtual ~Kitchen();

	virtual void	execute(void);

private:
	void		cook(APizza*) const;
	size_t	countOrdersSpots() const;

	void	handleCommand(std::string const &, Clock &);

private:
	std::string			_pathIn;
	std::string			_pathOut;
	Process*				_process;
	NamedPipe::In*		_fromReception;
	NamedPipe::Out*	_toReception;
	ThreadPool*			_cooks;

	size_t				_cooksCount;
	size_t				_resupplyTime;

	std::queue<APizza*>							_orders;
	std::map<APizza::Ingredients, size_t>	_supplies;

	bool					_dead;
};

#endif	/* KITCHEN_HPP */
