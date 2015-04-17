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
	std::cout << "Creating (read) " << path << std::endl;

	if (access(_path.c_str(), R_OK) == -1)
	{
		if (mkfifo(_path.c_str(), 0644) == -1)
			throw NamedPipe::Exception(std::string("NamedPipe::In::In: ") + strerror(errno));
	}
	_stream.open(_path);

	if (_stream.fail())
		throw NamedPipe::Exception("Couldn't open named pipe.");
}

NamedPipe::In::~In()
{
	std::cout << "Deleting (read) " << _path << std::endl;
	_stream.close();
	unlink(_path.c_str());
}

NamedPipe::In&	NamedPipe::In::operator>>(std::string & str)
{
	std::cout << "Reading " << _path << std::endl;

	std::getline(_stream, str);

	std::cout << "Done reading " << _path << std::endl;

	return (*this);
}

void	NamedPipe::In::read(std::string & str)
{
	*this >> str;
}

std::ifstream&	NamedPipe::In::getStream()
{
	return (_stream);
}

NamedPipe::Out::Out(std::string const & path)
	: APipe(path)
{
	std::cout << "Creating (write) " << _path << std::endl;
	if (access(_path.c_str(), W_OK) == -1)
	{
		if (mkfifo(_path.c_str(), 0644) == -1)
			throw NamedPipe::Exception(std::string("NamedPipe::Out::Out: ") + strerror(errno));
	}
	_stream.open(_path);

	if (_stream.fail())
		throw NamedPipe::Exception("Couldn't open named pipe.");
}

NamedPipe::Out::~Out()
{
	std::cout << "Deleting (write) " << _path << std::endl;
	_stream.close();
	unlink(_path.c_str());
}

NamedPipe::Out&	NamedPipe::Out::operator<<(std::string const & str)
{
	std::cout << "Writing " << _path << std::endl;
	_stream << str;

	return (*this);
}

void	NamedPipe::Out::write(std::string const & str)
{
	*this << str;
}
