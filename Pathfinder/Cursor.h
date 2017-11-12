/// \file Cursour.h
/// \brief Cursour that shows what node you are currently over.

#ifndef _CURSOUR_H_
#define _CURSOUR_H_
//File Includes
#include <SDL.h>
//Additional File Includes
#include "Sprite.h"

class Cursor : public Sprite
{
public:
	Cursor(SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h);//Cursour Constuctor
	~Cursor();//Cursour Destructor

	void Update();//Update Cursour
	int getMouseX(){ return m_mouseX; }//Get the Mouse X co-ordinate
	int getMouseY(){ return m_mouseY; }//Get the Mouse Y co-ordinate


private:
	int m_mouseX;//x co-ordinate
	int m_mouseY;//y co-ordinate
};

#endif // !_CURSOUR_H_


