/// \file Sprite.h
/// \brief Base sprite class.

#ifndef _SPRITE_H_
#define _SPRITE_H_
//File Includes
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Sprite {
public:
	Sprite(SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h, bool _canDeleteTex);//constructor for Sprite
	~Sprite();//Sprite Destructor

	void SetX(int _x) { m_position.x = _x; }//Set the X position of the sprite
	void SetY(int _y) { m_position.y = _y; }//Set the Y Position of the sprite

	int GetX() { return m_position.x; }//Get the X position of the sprite
	int GetY() { return m_position.y; }//Get the Y position of the sprite

	void setTexture(SDL_Texture* _tex);//Set the Texture of the sprite

	void Draw();//Draw the sprite
private:
	SDL_Renderer* m_renderer;//renderer used to draw
	SDL_Texture* m_image;//texture used by sprite
	SDL_Rect m_position;//position, width and height the sprite will be drawn with
	bool m_canDeleteTex;//if the sprite can delete its own texture
};

#endif // !_SPRITE_H_
