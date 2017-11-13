/// @file Cursor.cpp
/// @brief Controlls the cursour that shows what node you are on
#include "Cursor.h"

Cursor::Cursor( SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h ) :
	Sprite( _renderer, _tex, _x, _y, _w, _h, true )
{

}

Cursor::~Cursor()
{

}

void Cursor::Update()
{
	//normalizesd the position to the grid
	SDL_GetMouseState( &m_mouseX, &m_mouseY );
	SetX( (m_mouseX / 32) * 32 );
	SetY( (m_mouseY / 32) * 32 );
}