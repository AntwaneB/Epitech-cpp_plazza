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

	static Margarita*	newMargarita(APizza::SizePizza);

private:
	Margarita(APizza::SizePizza);

};

#endif	/* MARGARITA_HPP */
