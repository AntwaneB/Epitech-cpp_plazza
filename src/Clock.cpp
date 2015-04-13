/*
 * File:   Clock.cpp
 * Author: buchse_a
 *
 * Created on March 23, 2015, 1:27 PM
 */

#include <unistd.h>
#include <iostream>
#include "Clock.hpp"

Clock::Clock()
{
//	clock_gettime(CLOCK_REALTIME, &_timer);
	this->restart();
	_seconds = 0;
}

Clock::~Clock()
{
}
/*
struct timespec	Clock::getTimer() const
{
	return (_timer);
}
*/
long double Clock::elapsedTime() const
{
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	return (std::chrono::duration_cast<std::chrono::microseconds>(now - _timer).count());
}

void	Clock::restart()
{
	_timer = std::chrono::high_resolution_clock::now();
}

seconds_t	Clock::tick(void)
{
	_seconds += elapsedTime() / 1000000;
	this->restart();
	usleep(100);

	return (_seconds);
}

void	Clock::resetSec(void)
{
	_seconds = 0;
}