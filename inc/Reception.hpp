/*
 * File:   Reception.hpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 10:59 AM
 */

#ifndef RECEPTION_HPP
#define	RECEPTION_HPP

class Reception;

#include <utility>
#include <list>
#include <queue>
#include <vector>
#include "NamedPipe.hpp"
#include "KitchenFactory.hpp"
#include "APizza.hpp"

class Reception
{
public:
	Reception(double cookingTime, size_t cooksCount, size_t resupplyTime, bool gui);
	virtual ~Reception();

	void		start(void);
	void		guiListener(void);

private:
	void		createPizza(std::vector<std::string>);
	void		handleQueue(void);
	void		closeKitchens(void);
	std::pair<NamedPipe::In*, NamedPipe::Out*>	openKitchen(void);

private:
	std::map<APizza::TypePizza, APizza* (*)(APizza::SizePizza, double)>	_pizzasCtor;
	std::map<std::string, APizza::TypePizza>	_pizzaCvt;
	std::map<std::string, APizza::SizePizza>	_sizeCvt;

	double	_cookingTime;
	size_t	_cooksCount;
	size_t	_resupplyTime;

	std::list<std::pair<NamedPipe::In*, NamedPipe::Out*> >	_kitchens;
	std::queue<APizza*>													_orders;

	std::list<int>															_guiKitchens;
	std::pair<NamedPipe::In*, NamedPipe::Out*>					_guiPipes;

	bool	_gui;
};

#endif	/* RECEPTION_HPP */
