/*
 * File:   Process.cpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 4:19 PM
 */

#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <exception>
#include <iostream>
#include "Process.hpp"

Process::Process(ITask& task)
	: _pid(0), _status(Process::STOPPED)
{
	if ((_pid = fork()) == -1)
		throw Process::Exception(std::string("fork") + strerror(errno));

	if (_pid == 0)
	{
		try
		{
			task.execute();
			exit(0);
		} catch (std::exception const & e)
		{
			std::cerr << e.what() << std::endl;
			exit(-1);
		}
	}
	else
	{
		_status = Process::RUNNING;
	}
}

Process::~Process()
{
	this->wait();
}

void	Process::wait()
{
	if (_status == Process::RUNNING)
	{
		if (waitpid(_pid, NULL, 0) == -1)
			throw Process::Exception(std::string("waitpid") + strerror(errno));

		_status = Process::STOPPED;
	}
}