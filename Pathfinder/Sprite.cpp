/// @file Sprite.cpp
/// @brief The base Sprite class
#include "Sprite.h"

Sprite::Sprite( SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h, bool _canDeleteTex )
{
	m_image = _tex;//sets the texture

	m_position.x = _x;//sets the positons
	m_position.y = _y;
	m_position.h = _h;
	m_position.w = _w;
	//sets the m_renderer to use
	m_renderer = _renderer;//sets the renderer used
	m_canDeleteTex = _canDeleteTex;//if the sprite can delete its own texture
}

Sprite::~Sprite()
{
	if ( m_canDeleteTex )//if it can delete its own texture
	{
		if ( m_image )
			SDL_DestroyTexture( m_image );//delete texture
	}
}

void Sprite::setTexture( SDL_Texture* _tex )
{
	m_image = _tex;//set the texture
}

void Sprite::Draw()
{
	if ( m_image )
	{
		SDL_RenderCopy( m_renderer, m_image, NULL, &m_position );//render image to screen at position
	}
}