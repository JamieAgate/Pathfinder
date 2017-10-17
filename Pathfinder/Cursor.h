#pragma once
#include <SDL.h>
#include "Sprite.h"

class Cursor : public Sprite
{
public:
	Cursor(SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h);
	~Cursor();

	void update();
	int getMouseX(){ return mouseX; }
	int getMouseY(){ return mouseY; }


private:
	int mouseX;
	int mouseY;
};