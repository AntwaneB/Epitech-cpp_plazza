/*
 * File:   GUI.hpp
 * Author: buchse_a
 *
 * Created on April 21, 2015, 5:10 PM
 */

#ifndef GUI_HPP
#define	GUI_HPP

#include <QtWidgets>
#include <map>
#include "Graphics.hpp"
#include "ITask.hpp"
#include "NamedPipe.hpp"

class GUI : public QObject, public ITask
{
	Q_OBJECT

public:
	GUI(size_t);
	virtual ~GUI();

	void	execute(void);

public slots:
	void	updateWindow(void);

private:
	void	initWindow(void);
	void	initInputs(void);
	void	initCanvas(void);
	void	endInit(void);

private:
	bool							_initialized;
	size_t						_cooksPerKitchen;
	std::pair<NamedPipe::In*, NamedPipe::Out*> _guiPipes;

	QFrame*						_window;
	QGridLayout*				_layout;
	Graphics*					_canvas;

	std::map<std::string, QWidget*>	_components;
};

#endif	/* GUI_HPP */
