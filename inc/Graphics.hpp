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
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Graphics : public QSFMLCanvas
{
public:
	virtual ~Graphics();
	void 		initPizzeria();
	void 		onInit();
	void 		onUpdate();
private:
	size_t 							_nbKitchen;
	sf::RectangleShape 	_bigRect;
	sf::RectangleShape 	_littleRect;
	sf::Sprite 					_cook;
	sf::Sprite 					_nocook;
	size_t 							_height;
	size_t 							_width;
	size_t							_nbCook;
};

#endif	/* SDLGRAPHICS_HPP */
