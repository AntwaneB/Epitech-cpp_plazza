/*
 * File:   SDLGraphics.hpp
 * Author: buchse_a
 *
 * Created on March 24, 2015, 1:42 PM
 */

#ifndef GRAPHICS_HPP
#define	GRAPHICS_HPP

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "QSFMLCanvas.hpp"

class Graphics : public QSFMLCanvas
{
public:
	Graphics(QWidget* parent, const QPoint& position, const QSize& size, size_t, size_t);
	virtual ~Graphics();

	virtual void 		onInit();
	virtual void 		onUpdate();
	void					setDatas(std::vector<size_t> const &);

private:
	size_t 					_nbKitchen;
	size_t					_nbCooks;

	size_t					_colsK;
	size_t					_linesK;
	size_t					_colsC;
	size_t					_linesC;

	size_t					_winWidth;
	size_t					_winHeight;
	size_t					_kitchenWidth;
	size_t					_kitchenHeight;
	size_t					_cookWidth;
	size_t					_cookHeight;

	sf::RectangleShape 	_kitchenBorder;
	sf::RectangleShape 	_kitchenBody;
	sf::Sprite				 	_cookActive;
	sf::Sprite				 	_cookIdle;
	sf::Texture 				_tcookActive;
	sf::Texture 				_tcookIdle;

	std::vector<size_t>	_activeCooks;
};

#endif	/* SDLGRAPHICS_HPP */
