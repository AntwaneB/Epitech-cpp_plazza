/*
 * File:   GUI.hpp
 * Author: buchse_a
 *
 * Created on April 21, 2015, 5:10 PM
 */

#ifndef GUI_HPP
#define	GUI_HPP

#include <QtWidgets>
#include "Graphics.hpp"
#include "ITask.hpp"

class GUI : public QObject, public ITask
{
	Q_OBJECT

public:
	GUI();
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

	QFrame*						_window;
	QGridLayout*				_layout;
	Graphics*					_canvas;

	std::vector<QWidget*>	_components;
};

#endif	/* GUI_HPP */
