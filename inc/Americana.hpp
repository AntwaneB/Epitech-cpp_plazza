/*
 * File:   Americana.hpp
 * Author: buchse_a
 *
 * Created on April 16, 2015, 6:53 PM
 */

#ifndef AMERICAINE_HPP
#define	AMERICAINE_HPP

#include "APizza.hpp"

class Americaine : public APizza
{
public:
	virtual ~Americaine();

	static APizza*	newAmericaine(APizza::SizePizza, double);

private:
	Americaine(APizza::SizePizza, double);

};

#endif	/* AMERICAINE_HPP */
