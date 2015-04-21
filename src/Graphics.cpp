/*
 * Author: buchse_a
 * File:   SDLGraphics.cpp
 *
 * Created on March 24, 2015, 1:42 PM
 */

#include <Graphics.hpp>
#include	"math.h"

Graphics::Graphics(QWidget* parent, const QPoint& position, const QSize& size, size_t nbKitchen, size_t nbCooks)
	: QSFMLCanvas(parent, position, size), _nbKitchen(nbKitchen), _nbCooks(nbCooks)
{
}

void Graphics::onInit()
{
	_winWidth = 778;
	_winHeight = 512;

	_colsK = static_cast<int>(ceil(sqrt(_nbKitchen)));
	_linesK = static_cast<int>(floor(sqrt(_nbKitchen)));

	_kitchenWidth = _winWidth / _colsK - 1;
	_kitchenHeight = _winHeight / _linesK - 1;

	_colsC = static_cast<int>(ceil(sqrt(_nbCooks)));
	_linesC = static_cast<int>(floor(sqrt(_nbCooks)));

	_cookWidth = _kitchenWidth / _colsC;
	_cookHeight = _kitchenHeight / _linesC;

	_kitchenBorder.setSize(sf::Vector2f(_kitchenWidth, _kitchenHeight));
	_kitchenBorder.setFillColor(sf::Color::Black);
	_kitchenBody.setSize(sf::Vector2f(_kitchenWidth - 4, _kitchenHeight - 4));
	_kitchenBody.setFillColor(sf::Color(128, 128, 128));

	this->clear(sf::Color(128, 128, 128));
}

void Graphics::onUpdate()
{
	size_t x = 1;
	size_t y = 1;

	size_t j = 1;
	for (size_t i = 1; i <= _nbKitchen; i++)
	{
		_kitchenBorder.setPosition(x, y);
		_kitchenBody.setPosition(x + 2, y + 2);
		this->draw(_kitchenBorder);
		this->draw(_kitchenBody);

		x += _kitchenWidth + 1;
		if (i / j >= _colsK)
		{
			x = 1;
			y += _kitchenHeight + 1;
			j++;
		}
	}
}

Graphics::~Graphics()
{
}
