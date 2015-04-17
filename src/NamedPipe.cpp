/*
 * File:   NamedPipe.cpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 2:40 PM
 */

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
	_stream.open(_path);

	if (_stream.fail())
		throw NamedPipe::Exception("Couldn't open named pipe.");
}

NamedPipe::In::~In()
{
	_stream.close();
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
	_stream.open(_path);

	if (_stream.fail())
		throw NamedPipe::Exception("Couldn't open named pipe.");
}

NamedPipe::Out::~Out()
{
	_stream.close();
}

NamedPipe::Out&	NamedPipe::Out::operator<<(std::string const & str)
{
	_stream << str;

	return (*this);
}
