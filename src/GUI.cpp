/*
 * File:   GUI.cpp
 * Author: buchse_a
 *
 * Created on April 21, 2015, 5:10 PM
 */

#include "GUI.hpp"

GUI::GUI()
	: _initialized(false)
{
}

GUI::~GUI()
{
	if (_initialized)
	{
		for (size_t i = 0; i < _components.size(); i++)
			delete _components[i];
		delete _canvas;
		delete _layout;
		delete _window;
	}
}

void GUI::execute(void)
{
	if (!_initialized)
	{
		int ac = 1; char *av[] = { strdup("./plazza") };
		QApplication app(ac, av);

		this->initWindow();
		this->initInputs();
		this->initCanvas();

		this->endInit();

		QTimer *timer = new QTimer;
	   QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateWindow()));
		timer->start(500);

		app.exec();
	}
}

void GUI::initWindow()
{
	_window = new QFrame;

	_window->setFixedSize(800, 600);
	_window->setWindowTitle("The Plazza");
	_window->setGeometry(
		QStyle::alignedRect(
		Qt::LeftToRight,
		Qt::AlignCenter,
		_window->size(),
		qApp->desktop()->availableGeometry()
	));

	_layout = new QGridLayout;
}

void GUI::initInputs()
{
	QComboBox*	pizzaType = new QComboBox;
	pizzaType->addItem("Margarita");
	pizzaType->addItem("Americaine");
	pizzaType->addItem("Regina");
	pizzaType->addItem("Fantasia");

	QComboBox*	pizzaSize = new QComboBox;
	pizzaSize->addItem("S");
	pizzaSize->addItem("M");
	pizzaSize->addItem("L");
	pizzaSize->addItem("XL");
	pizzaSize->addItem("XXL");

	QSpinBox*	pizzaCount = new QSpinBox;
	pizzaCount->setMinimum(1);
	pizzaCount->setMaximum(999);

	QPushButton*	submitBtn = new QPushButton("Passer la commande");
	submitBtn->setFixedHeight(60);

	QLineEdit*	input = new QLineEdit;

	_layout->addWidget(pizzaType, 1, 0);
	_layout->addWidget(pizzaSize, 1, 1);
	_layout->addWidget(pizzaCount, 1, 2);
	_layout->addWidget(submitBtn, 1, 3, 2, 1);
	_layout->addWidget(input, 2, 0, 1, 3);

	_components.push_back(pizzaType);
	_components.push_back(pizzaSize);
	_components.push_back(pizzaCount);
	_components.push_back(submitBtn);
	_components.push_back(input);
}

void GUI::initCanvas()
{
	_canvas = new Graphics(_window, QPoint(20, 20), QSize(360, 360), 0, 5); // TEMPORAIRE
	_canvas->show();

	_layout->addWidget(_canvas, 0, 0, 1, 4);
}

void GUI::endInit()
{
	_window->setLayout(_layout);
	_window->show();

	_initialized = true;
}

void GUI::updateWindow()
{
	static int i = 0;

	i++;
	if (i == 10)
	{
		QPushButton*	test = new QPushButton("Test");
		_layout->addWidget(test, 3, 0, 1, 4);
		_components.push_back(test);
	}
	std::cout << "hey" << std::endl;
}
