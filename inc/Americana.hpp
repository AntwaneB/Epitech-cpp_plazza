/*
 * File:   Americana.hpp
 * Author: buchse_a
 *
 * Created on April 16, 2015, 6:53 PM
 */

#ifndef AMERICANA_HPP
#define	AMERICANA_HPP

#include "APizza.hpp"

class Americana : public APizza
{
public:
	virtual ~Americana();

	static APizza*	newAmericana(APizza::SizePizza, double);

private:
	Americana(APizza::SizePizza, double);

};

#endif	/* AMERICANA_HPP */
