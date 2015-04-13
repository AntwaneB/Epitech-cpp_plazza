/*
 * File:   Process.hpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 4:19 PM
 */

#ifndef PROCESS_HPP
#define	PROCESS_HPP

#include <unistd.h>
#include <stdexcept>
#include "ITask.hpp"

class Process
{
public:
	class Exception : public std::runtime_error
	{
	public:
		Exception(std::string const & s) : std::runtime_error(s), _message(s) {};
		virtual ~Exception() throw() {};
		virtual const char* what() const throw() { return (_message.c_str()); }

	protected:
		std::string _message;
	};

public:
	enum Status { RUNNING, STOPPED };

public:
	Process(ITask&);
	virtual ~Process();

	void	wait(void);

private:
	pid_t					_pid;
	Process::Status	_status;
};

#endif	/* PROCESS_HPP */
