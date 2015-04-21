/*
 * File:   Canvas.hpp
 * Author: buchse_a
 *
 * Created on April 21, 2015, 11:16 AM
 */

#ifndef CANVAS_HPP
#define	CANVAS_HPP

#include "QSFMLCanvas.hpp"

class Canvas : public QSFMLCanvas
{
public:
	Canvas(QWidget* parent, const QPoint& position, const QSize& size);
	virtual ~Canvas();

private:
	void	onInit();
	void	onUpdate();

private:
	sf::Texture	_texture;
	sf::Sprite	_sprite;
	sf::Clock	_clock;
};

#endif	/* CANVAS_HPP */
