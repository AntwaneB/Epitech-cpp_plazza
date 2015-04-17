/*
 * File:   StringHelper.cpp
 * Author: buchse_a
 *
 * Created on April 17, 2015, 3:33 PM
 */

#include "StringHelper.hpp"

StringHelper::StringHelper()
{
}

StringHelper::~StringHelper()
{
}

bool	StringHelper::inStr(char const c, std::string const & str)
{
	for (size_t i = 0; i < str.size(); i++)
		if (str[i] == c)
			return (true);
	return (false);
}

std::vector<std::string>		StringHelper::strtovec(std::string const & str, std::string const & delim)
{
	std::vector<std::string>	res;

	std::string	tmp = "";
	size_t		len = str.size();
	for (size_t i = 0; i < len; i++)
	{
		if (inStr(str[i], delim))
		{
			if (!tmp.empty())
			res.push_back(tmp);
			tmp.clear();
		}
		else
			tmp += str[i];
	}
	if (!tmp.empty())
		res.push_back(tmp);

	return (res);
}
