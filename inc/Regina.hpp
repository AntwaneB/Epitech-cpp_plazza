#ifndef REGINA_HPP
#define	REGINA_HPP

#include "APizza.hpp"

class Regina : public APizza
{
public:
	virtual ~Regina();

	static APizza*	newRegina(APizza::SizePizza, double);

private:
	Regina(APizza::SizePizza, double);

};

#endif	/* REGINA_HPP */
