/*
 ** App.cpp
 **
 ** Made by Antoine Buchser
 ** Login   <buchse_a@epitech.eu>
 **
 ** Started on February 6, 2015, 10:53 AM Antoine Buchser
 ** Updated on February 6, 2015, 10:53 AM Antoine Buchser
 */

#include <iostream>
#include <unistd.h>
#include <QApplication>
#include <QtWidgets>
#include <SFML/Window/Window.hpp>
#include "Exception.hpp"
#include "App.hpp"
#include "Thread.hpp"
#include "Reception.hpp"
#include "Canvas.hpp"

App::App(int ac, char** av)
	: _ac(ac), _av(av), _GUIThread(NULL)
{
	if (!this->validateArgs())
		throw ArgumentsException("usage:\n" \
										 "./plazza [cooking time] [cooks per kitchen] [resupply time]");
}

App::~App()
{
	if (this)
	{
	}
}

bool	App::validateArgs() const
{
	if (_ac != 4 || atoi(_av[1]) < 0 || atoi(_av[2]) < 0 || atoi(_av[3]) < 0)
		return (false);
	return (true);
}

Thread*	App::getGuiThread()
{
	return (_GUIThread);
}

void	App::drawGui() const
{
	int ac = 1;
	char *av[1] = { strdup("./plazza") };
	QApplication app(ac, av);

	QFrame window;
	window.setFixedSize(800, 600);
	window.setWindowTitle("The Plazza");
	window.setGeometry(
		QStyle::alignedRect(
		Qt::LeftToRight,
		Qt::AlignCenter,
		window.size(),
		qApp->desktop()->availableGeometry()
	));

	QComboBox	pizzaType;
	pizzaType.addItem("Margarita");
	pizzaType.addItem("Americaine");
	pizzaType.addItem("Regina");
	pizzaType.addItem("Fantasia");

	QComboBox	pizzaSize;
	pizzaSize.addItem("S");
	pizzaSize.addItem("M");
	pizzaSize.addItem("L");
	pizzaSize.addItem("XL");
	pizzaSize.addItem("XXL");

	QSpinBox		count;
	count.setMinimum(1);

	QPushButton	submitBtn("Passer la commande");

//	QTextEdit	textarea;
	Canvas*		canvas = new Canvas(&window, QPoint(20, 20), QSize(360, 360));
	canvas->show();

	QGridLayout* layout = new QGridLayout;
	layout->addWidget(canvas, 0, 0, 1, 4);
	layout->addWidget(&pizzaType, 1, 0);
	layout->addWidget(&pizzaSize, 1, 1);
	layout->addWidget(&count, 1, 2);
	layout->addWidget(&submitBtn, 1, 3);

	window.setLayout(layout);
	window.show();

	app.exec();
}

void*	runGui(void* arg)
{
	App*	app = static_cast<App*>(arg);

	app->drawGui();

	return (NULL);
}

int	App::run()
{
	try
	{
//		_GUIThread = new Thread;
//		_GUIThread->run(&runGui, this);
		runGui(this);


		Reception	reception(atof(_av[1]), atoi(_av[2]), atoi(_av[3]));

		reception.start();
	}
	catch (std::exception const & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}
