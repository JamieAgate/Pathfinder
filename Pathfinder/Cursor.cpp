#include "Cursor.h"

Cursor::Cursor(SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h) :
	Sprite(_renderer, _tex, _x, _y, _w, _h)
{

}

Cursor::~Cursor()
{

}

void Cursor::update()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	SetX((mouseX / 32) * 32);
	SetY((mouseY / 32) * 32);
}