/*
 * Author: buchse_a
 * File:   SDLGraphics.cpp
 *
 * Created on March 24, 2015, 1:42 PM
 */

#include <SFML/Graphics.hpp>
#include <Graphics.hpp>
#include	"math.h"

Graphics::Graphics(size_t kitchen)
{
	(void)kitchen;
	sf::RenderWindow win(sf::VideoMode(800, 600), "06 45 36 41 47");
	/*if (XInitThreads() == 0)
		exit (EXIT_FAILURE);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exit (EXIT_FAILURE);
	if ((this->_win = SDL_SetVideoMode(800, 600, 32, SDL_ANYFORMAT)) == NULL)
		exit (EXIT_FAILURE);
	SDL_WM_SetCaption("06 45 36 41 47", NULL);
	size_t cols = static_cast<int>(ceil(sqrt(kitchen)));
	size_t lines = static_cast<int>(floor(sqrt(kitchen)));
	this->_height = 600 / lines;
	this->_width = 800 / cols;
	this->_kitchen = kitchen;
	this->_bigRect = SDL_CreateRGBSurface(0, this->_width, this->_height, 32, 0, 0, 0, 0);
	SDL_FillRect(this->_bigRect, NULL, SDL_MapRGB(this->_bigRect->format, 255, 0, 0));
	this->_littleRect = SDL_CreateRGBSurface(0, this->_width - 2, this->_height - 2, 32, 0, 0, 0, 0);
	SDL_FillRect(this->_littleRect, NULL, SDL_MapRGB(this->_littleRect->format, 0, 0, 0));*/
}

Graphics::~Graphics()
{

}

void Graphics::initPizzeria()
{
/*	size_t i;
	SDL_Rect		pos;

	pos.x = 0;
	pos.y = 0;
	SDL_Surface	*resize;

	for (i = 0; i < this->_kitchen; i++)
		{
			SDL_BlitSurface(this->_bigRect, NULL, this->_win, &pos);
			SDL_BlitSurface(this->_littleRect, NULL, this->_win, &pos);
			pos.x += this->_width;
			if (pos.x >= 800)
			{
				pos.x = 0;
				pos.y += this->_height;
			}
		}
	resize = SDL_ScaleSurface(this->_bigRect, 300, 300);
	SDL_BlitSurface(resize, NULL, this->_win, NULL);
	SDL_Flip(this->_win);*/
}

void	Graphics::winRefresh()
{
	//SDL_Flip(this->_win);
}
