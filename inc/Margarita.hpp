/*
 * File:   Margarita.hpp
 * Author: buchse_a
 *
 * Created on April 16, 2015, 6:53 PM
 */

#ifndef MARGARITA_HPP
#define	MARGARITA_HPP

#include "APizza.hpp"

class Margarita : public APizza
{
public:
	virtual ~Margarita();

	static APizza*	newMargarita(APizza::SizePizza, double);

private:
	Margarita(APizza::SizePizza, double);

};

#endif	/* MARGARITA_HPP */
