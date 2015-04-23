/*
 * File:   NamedPipe.cpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 2:40 PM
 */

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include "Mutex.hpp"
#include "ScopedLock.hpp"
#include "NamedPipe.hpp"

NamedPipe::APipe::APipe(std::string const & path)
	: _path(path)
{
}

NamedPipe::APipe::~APipe()
{
}

NamedPipe::In::In(std::string const & path)
	: APipe(path)
{
	Mutex	mutex;
	ScopedLock lock(mutex);
	if (access(_path.c_str(), R_OK) == -1)
	{
		if (mkfifo(_path.c_str(), 0644) == -1)
			if (errno != EEXIST)
				throw NamedPipe::Exception(std::string("NamedPipe::In::In: ") + strerror(errno) + _path);
	}

	_stream.open(_path);

	if (_stream.fail())
		throw NamedPipe::Exception("Couldn't open named pipe.");
}

NamedPipe::In::~In()
{
	_stream.close();
	unlink(_path.c_str());
}

NamedPipe::In&	NamedPipe::In::operator>>(std::string & str)
{
	if (this && _stream.good())
		std::getline(_stream, str);

	return (*this);
}

void	NamedPipe::In::read(std::string & str)
{
	this->operator>>(str);
}

NamedPipe::Out::Out(std::string const & path)
	: APipe(path)
{
	Mutex	mutex;
	mutex.lock();
	if (access(_path.c_str(), W_OK) == -1)
	{
		if (mkfifo(_path.c_str(), 0644) == -1)
			if (errno != EEXIST)
				throw NamedPipe::Exception(std::string("NamedPipe::Out::Out: ") + strerror(errno));
	}

	_stream.open(_path);

	if (_stream.fail())
		throw NamedPipe::Exception("Couldn't open named pipe.");
	mutex.unlock();
}

NamedPipe::Out::~Out()
{
	_stream.close();
	unlink(_path.c_str());
}

NamedPipe::Out&	NamedPipe::Out::operator<<(std::string const & str)
{
	if (this && _stream.good())
		_stream << str << std::endl;

	return (*this);
}

void	NamedPipe::Out::write(std::string const & str)
{
	this->operator<<(str);
}
