/*
 * Author: buchse_a
 * File:   SDLGraphics.cpp
 *
 * Created on March 24, 2015, 1:42 PM
 */

#include <Graphics.hpp>
#include	"math.h"

Graphics::Graphics(QWidget* parent, const QPoint& position, const QSize& size, size_t nbKitchen, size_t nbCook)
	: QSFMLCanvas(parent, position, size), _nbKitchen(nbKitchen), _nbCook(nbCook)
{
}

void Graphics::onInit()
{
	size_t cols = static_cast<int>(ceil(sqrt(_nbKitchen)));
	size_t lines = static_cast<int>(floor(sqrt(_nbKitchen)));
	size_t ccols = static_cast<int>(ceil(sqrt(_nbCook)));
	size_t clines = static_cast<int>(floor(sqrt(_nbCook)));

//	this->_window.create(sf::VideoMode(778 + cols, 545 + lines), "06 45 36 41 47");
	this->_height = 545 / lines;
	this->_width = 778 / cols;

	this->clear(sf::Color::Black);
	_bigRect.setSize(sf::Vector2f(_width, _height));
	_littleRect.setSize(sf::Vector2f(_width - 2, _height - 2));
	_bigRect.setFillColor(sf::Color::Red);
	_littleRect.setFillColor(sf::Color::Black);

	sf::Texture tcook;
	tcook.loadFromFile("assets/cook.png");
	_cook.setTexture(tcook);
	(void)clines;
	(void)ccols;
	//_cook.setScale(sf::Vector2f(0.5f, 0.5f));

	/*std::cout << "lol2" << std::endl;
	sf::Image nocook;
	cook.loadFromFile("./cook.png");
	sf::Texture tnocook;
	tcook.loadFromImage(nocook);
	_nocook.setTexture(tnocook);
	std::cout << "lol3" << std::endl;*/
	//_nocook.setScale(sf::Vector2f(_height / ccols * 0.03f, _height / clines * 0.03f));
}

void Graphics::onUpdate()
{

}

Graphics::~Graphics()
{

}

void Graphics::initPizzeria()
{
	size_t		i;
	int				x;
	int				y;

	x = 1;
	y = 1;

	for (i = 0; i < this->_nbKitchen; i++)
		{
			_bigRect.setPosition(x, y);
			_littleRect.setPosition(x + 1, y + 1);
			this->draw(_bigRect);
			this->draw(_littleRect);
			x += this->_width + 1;
			if (x >= 800)
			{
				x = 1;
				y += this->_height + 1;
			}
		}
		this->draw(_cook);
}
