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

	void	refillSupplies(void);
	void	checkActivity(void);

private:
	void		cook(APizza*) const;
	size_t	countOrdersSpots() const;

	void	handleCommand(std::string &);
	bool	handleDead(std::string const & command);
	bool	handleCount(std::string const & command);
	bool	handleCook(std::string const & command);
	bool	handleCanCook(std::string const & command);
	bool	handleDie(std::string const & command);

private:
	std::string			_pathIn;
	std::string			_pathOut;
	Process*				_process;
	NamedPipe::In*		_fromReception;
	NamedPipe::Out*	_toReception;
	ThreadPool*			_cooks;

	size_t				_cooksCount;
	size_t				_resupplyTime;

	std::queue<APizza*>						_orders;
	std::map<APizza::Ingredients, int>	_supplies;

	bool					_dead;
	seconds_t			_lifeTime;
	Clock					_lifeClock;
};

#endif	/* KITCHEN_HPP */
