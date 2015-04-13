/*
 * File:   ITask.hpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 4:21 PM
 */

#ifndef ITASK_HPP
#define	ITASK_HPP

class ITask
{
public:
	virtual ~ITask();
	virtual void	execute(void) = 0;
};

#endif	/* ITASK_HPP */
