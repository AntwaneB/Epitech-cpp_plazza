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
	if (access(_path.c_str(), R_OK) == -1)
	{
		if (mkfifo(_path.c_str(), 0644) == -1)
			throw NamedPipe::Exception(std::string("NamedPipe::In::In: ") + strerror(errno));
	}

	_stream.open(_path);

	if (_stream.fail())
		throw NamedPipe::Exception("Couldn't open named pipe.");

	std::cerr << "Creating (read) " << _path << std::endl;
}

NamedPipe::In::~In()
{
	std::cout << "Deleting (read) " << _path << std::endl;
	_stream.close();
	unlink(_path.c_str());
}

NamedPipe::In&	NamedPipe::In::operator>>(std::string & str)
{
	std::cout << "Reading (" << getpid() << ")" << _path << std::endl;

	std::getline(_stream, str);

	std::cout << "Done reading (" << getpid() << ")" << _path << std::endl;

	return (*this);
}

void	NamedPipe::In::read(std::string & str)
{
	this->operator>>(str);
}

NamedPipe::Out::Out(std::string const & path)
	: APipe(path)
{
	if (access(_path.c_str(), W_OK) == -1)
	{
		if (mkfifo(_path.c_str(), 0644) == -1)
			throw NamedPipe::Exception(std::string("NamedPipe::Out::Out: ") + strerror(errno));
	}
	_stream.open(_path);

	if (_stream.fail())
		throw NamedPipe::Exception("Couldn't open named pipe.");

	std::cout << "Creating (write) " << _path << std::endl;
}

NamedPipe::Out::~Out()
{
	std::cout << "Deleting (write) " << _path << std::endl;
	_stream.close();
	unlink(_path.c_str());
}

NamedPipe::Out&	NamedPipe::Out::operator<<(std::string const & str)
{
	std::cout << "Writing " << _path;
	_stream << str << std::endl;
	std::cout << " --- Done writing " << _path << std::endl;

	return (*this);
}

void	NamedPipe::Out::write(std::string const & str)
{
	this->operator<<(str);
}
