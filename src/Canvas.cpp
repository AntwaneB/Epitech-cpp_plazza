/*
 * File:   Canvas.cpp
 * Author: buchse_a
 *
 * Created on April 21, 2015, 11:16 AM
 */

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Canvas.hpp"

Canvas::Canvas(QWidget* parent, const QPoint& position, const QSize& size)
	: QSFMLCanvas(parent, position, size)
{
}

Canvas::~Canvas()
{
}

void Canvas::onInit()
{
	_texture.loadFromFile("assets/test.jpg");

	_sprite.setTexture(_texture);
	_sprite.setPosition(sf::Vector2f(_texture.getSize()) / 4.f);
	_sprite.setOrigin(sf::Vector2f(_texture.getSize()) / 2.f);

	_clock.restart();
}

void Canvas::onUpdate()
{
	this->clear(sf::Color(128, 128, 128));

	_sprite.rotate(_clock.getElapsedTime().asSeconds() * 100.f);

	this->draw(_sprite);

	_clock.restart();
}