/*
 * File:   StringHelper.hpp
 * Author: buchse_a
 *
 * Created on April 17, 2015, 3:33 PM
 */

#ifndef STRINGHELPER_HPP
#define	STRINGHELPER_HPP

#include <vector>
#include <string>

class StringHelper
{
public:
	virtual ~StringHelper();
	static bool								inStr(char const, std::string const &);
	static std::vector<std::string>	strtovec(std::string const &, std::string const &);

private:
	StringHelper();
};

#endif	/* STRINGHELPER_HPP */
