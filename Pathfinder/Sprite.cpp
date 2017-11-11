#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h, bool _canDeleteTex)
{
	image = _tex;
	
	position.x = _x;
	position.y = _y;
	position.h = _h;
	position.w = _w;
	//sets the renderer to use
	renderer = _renderer;
	canDeleteTex = _canDeleteTex;
}

Sprite::~Sprite()
{
	if (canDeleteTex)
	{
		if (image)
			SDL_DestroyTexture(image);
	}
}

void Sprite::setTexture(SDL_Texture* _tex)
{
	image = _tex;
}

void Sprite::Draw()
{
	if (image)
	{
		SDL_RenderCopy(renderer, image, NULL, &position);//render image to screen at position
	}
}