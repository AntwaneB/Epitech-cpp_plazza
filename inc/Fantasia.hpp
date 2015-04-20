/*
 * File:   FANTASIA.hpp
 * Author: buchse_a
 *
 * Created on April 16, 2015, 6:53 PM
 */

#ifndef FANTASIA_HPP
#define	FANTASIA_HPP

#include "APizza.hpp"

class Fantasia : public APizza
{
public:
	virtual ~Fantasia();

	static APizza*	newFantasia(APizza::SizePizza, double);

private:
	Fantasia(APizza::SizePizza, double);

};

#endif	/* FANTASIA_HPP */
