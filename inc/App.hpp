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
	Thread*	getGuiThread(void);

private:
	bool	validateArgs(void) const;
	bool	isDigitalString(std::string str) const;

private:
	int			_ac;
	char**		_av;

	Thread*		_GUIThread;
};

#endif /* !APP_HPP */
