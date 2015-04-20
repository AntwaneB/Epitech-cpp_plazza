/*
 * File:   SDLGraphics.hpp
 * Author: buchse_a
 *
 * Created on March 24, 2015, 1:42 PM
 */

#ifndef GRAPHICS_HPP
#define	GRAPHICS_HPP

/*#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <X11/Xlib.h>*/
#include <iostream>
#include <sstream>
#include <map>

class Graphics
{
public:
	Graphics(size_t);
	virtual ~Graphics();
	void 		initPizzeria();
	void		winRefresh();

private:
	/*SDL_Surface		*_win;
	size_t 				_kitchen;
	SDL_Surface 	*_bigRect;
	SDL_Surface 	*_littleRect;
	size_t 				_height;
	size_t 				_width;*/
};

#endif	/* SDLGRAPHICS_HPP */
