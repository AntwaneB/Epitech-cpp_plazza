/*
 * File:   GUI.cpp
 * Author: buchse_a
 *
 * Created on April 21, 2015, 5:10 PM
 */

#include "GUI.hpp"
#include "Mutex.hpp"
#include "ScopedLock.hpp"
#include "StringHelper.hpp"

GUI::GUI(size_t cooksPerKitchen)
	: _initialized(false), _cooksPerKitchen(cooksPerKitchen)
{
}

GUI::~GUI()
{
	if (_initialized)
	{
		for (std::map<std::string, QWidget*>::iterator it = _components.begin(); it != _components.end(); ++it)
			delete it->second;
		delete _canvas;
		delete _layout;
		delete _window;
	}
}

void GUI::execute(void)
{
	if (!_initialized)
	{
		NamedPipe::Out*	out = new NamedPipe::Out("/tmp/buchse_a_from-gui");
		NamedPipe::In*		in = new NamedPipe::In("/tmp/buchse_a_to-gui");
		_guiPipes.first = in;
		_guiPipes.second = out;

		int ac = 1; char *av[] = { strdup("./plazza") };
		QApplication app(ac, av);

		this->initWindow();
		this->initInputs();
		this->initCanvas();

		this->endInit();

		QTimer *timer = new QTimer;
		QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateWindow()));
		QObject::connect(_components.find("submitBtn")->second, SIGNAL(clicked()), this, SLOT(manageInput()));
		timer->start(1000);

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

	_components.insert(std::map<std::string, QWidget*>::value_type("pizzaType", pizzaType));
	_components.insert(std::map<std::string, QWidget*>::value_type("pizzaSize", pizzaSize));
	_components.insert(std::map<std::string, QWidget*>::value_type("pizzaCount", pizzaCount));
	_components.insert(std::map<std::string, QWidget*>::value_type("submitBtn", submitBtn));
	_components.insert(std::map<std::string, QWidget*>::value_type("input", input));
}

void GUI::initCanvas()
{
	_canvas = new Graphics(_window, QPoint(20, 20), QSize(360, 360), 0, _cooksPerKitchen); // TEMPORAIRE
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
	(*_guiPipes.second) << "get_kitchens";

	std::string result;
	(*_guiPipes.first) >> result;
	if (!result.empty())
	{
		result = result.substr(9);
		result = result.substr(0, result.size() - 1);
	}

	std::vector<size_t> activeCooks;

	if (!result.empty())
	{
		std::vector<std::string>	kitchens = StringHelper::strtovec(result, " ");

		for (std::vector<std::string>::const_iterator it = kitchens.begin(); it != kitchens.end(); ++it)
			activeCooks.push_back(_cooksPerKitchen - std::stoi(*it));

		_canvas->setDatas(activeCooks);
	}
	else
		_canvas->setDatas(activeCooks);
}

void GUI::manageInput(void)
{
	try
	{
		std::cout << dynamic_cast<QComboBox*>(_components.find("pizzaType")->second)->currentText().toStdString() << std::endl;
		std::cout << dynamic_cast<QComboBox*>(_components.find("pizzaSize")->second)->currentText().toStdString() << std::endl;
		std::cout << dynamic_cast<QSpinBox*>(_components.find("pizzaCount")->second)->text().toStdString() << std::endl;
		std::cout << dynamic_cast<QLineEdit*>(_components.find("input")->second)->text().toStdString() << std::endl;

		std::string order = "";
		(*_guiPipes.second) << std::string("order ") + order;
	} catch (std::bad_cast const & e)
	{
		std::cerr << e.what() << std::endl;
	}
}
