/*
 ** App.hpp
 **
 ** Made by Antoine Buchser
 ** Login   <buchse_a@epitech.eu>
 **
 ** Started on February 6, 2015, 10:53 AM Antoine Buchser
 ** Updated on February 6, 2015, 10:53 AM Antoine Buchser
 */

#ifndef APP_HPP
#define	APP_HPP

#include <string>
#include <Thread.hpp>

class App
{
public:
	App(int, char**);
	~App();

	int	run(void);
	void	drawGui(void) const;

private:
	bool	validateArgs(void) const;

private:
	int			_ac;
	char**		_av;

	bool			_gui;
};

#endif /* !APP_HPP */
