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
}

NamedPipe::In::~In()
{
	_stream.close();
	unlink(_path.c_str());
}

NamedPipe::In&	NamedPipe::In::operator>>(std::string & str)
{
	std::stringstream sstm;
	sstm << _stream.rdbuf();

	str = sstm.str();

	return (*this);
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
}

NamedPipe::Out::~Out()
{
	_stream.close();
	unlink(_path.c_str());
}

NamedPipe::Out&	NamedPipe::Out::operator<<(std::string const & str)
{
	_stream << str;

	return (*this);
}
