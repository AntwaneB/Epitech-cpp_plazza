/*
 * File:   Clock.hpp
 * Author: buchse_a
 *
 * Created on March 23, 2015, 1:27 PM
 */

#ifndef CLOCK_HPP
#define	CLOCK_HPP

#include <time.h>
#include <chrono>

typedef long double	seconds_t;

class Clock
{
public:
	Clock();
	virtual ~Clock();

	seconds_t	tick(void);
	long double	elapsedTime(void) const;
	void			restart(void);
	void			resetSec(void);

private:
	std::chrono::high_resolution_clock::time_point	_timer;
	seconds_t			_seconds;
};

#endif	/* CLOCK_HPP */
