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
#include <vector>
#include "Kitchen.hpp"
#include "APizza.hpp"

class Reception
{
public:
	Reception(double cookingTime, size_t cooksCount, size_t resupplyTime);
	virtual ~Reception();

	void	start(void);

private:
	bool								inStr(char const, std::string const &);
	std::vector<std::string>	strtovec(std::string const &, std::string const &);
	void								createPizza(std::vector<std::string>);

	std::string	openKitchen(void);
	void			handleQueue(void);

	double	_cookingTime;
	size_t	_cooksCount;
	size_t	_resupplyTime;

	std::list<std::string>	_kitchens;
	std::queue<APizza*>		_orders;
};

#endif	/* RECEPTION_HPP */
