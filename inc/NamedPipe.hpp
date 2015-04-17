/*
 * File:   NamedPipe.hpp
 * Author: buchse_a
 *
 * Created on April 13, 2015, 2:40 PM
 */

#ifndef NAMEDPIPE_HPP
#define	NAMEDPIPE_HPP

#include <sys/types.h>
#include <sys/stat.h>
#include <stdexcept>
#include <string>
#include <fstream>

namespace NamedPipe
{
	class Exception : public std::runtime_error
	{
	public:
		Exception(std::string const & s) : std::runtime_error(s), _message(s) {};
		virtual ~Exception() throw() {};
		virtual const char* what() const throw() { return (_message.c_str()); }

	protected:
		std::string _message;
	};

	class APipe
	{
	public:
		APipe(std::string const &);
		virtual ~APipe();

	protected:
		std::string	_path;
	};

	class In : public APipe
	{
	public:
		In(std::string const &);
		virtual ~In();

		In&	operator>>(std::string &);

	private:
		std::ifstream	_stream;
	};

	class Out : public APipe
	{
	public:
		Out(std::string const &);
		virtual ~Out();

		Out&	operator<<(std::string const &);

	private:
		std::ofstream	_stream;
	};
}

#endif	/* NAMEDPIPE_HPP */
