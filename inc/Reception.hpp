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
#include <vector>
#include "Kitchen.hpp"

class Reception
{
public:
	Reception();
	virtual ~Reception();

	void	start(void);

private:
	bool	inStr(char const, std::string const &);
	std::vector<std::string>	strtovec(std::string const &, std::string const &);
	size_t	_cookingTime;
	size_t	_cooksCount;
	size_t	_resupplyTime;

	std::list<Kitchen*>	_kitchens;
};

#endif	/* RECEPTION_HPP */
