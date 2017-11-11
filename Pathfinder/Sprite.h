#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Sprite {
public:
	Sprite(SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h, bool _canDeleteTex);
	~Sprite();

	void SetX(int _x) { position.x = _x; }
	void SetY(int _y) { position.y = _y; }

	int GetX() { return position.x; }
	int GetY() { return position.y; }

	void setTexture(SDL_Texture* _tex);

	void Draw();
private:
	SDL_Renderer* renderer;
	SDL_Texture* image;
	SDL_Rect position;
	bool canDeleteTex;
};