#include "Player.h"

Player::Player(SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h, bool _canDeleteTex, std::vector<Node*> _grid) :
	Sprite(_renderer, _tex, _x, _y, _w, _h, _canDeleteTex)
{
	inputDelay = SDL_GetTicks() + 200;
	grid = _grid;
	currentNode = grid.at(_x / 32 * 30 + _y / 32);
}

Player::~Player()
{

}

void Player::Update()
{
	const Uint8* key = SDL_GetKeyboardState(NULL);
	if (SDL_GetTicks() > inputDelay)
	{
		if (key[SDL_SCANCODE_W] && grid.at((GetX()/32 *30 + GetY()/32)- 1)->getIsMoveable())
		{
			SetY((GetY() - 32));
			inputDelay = SDL_GetTicks() + 200;
		}
		if (key[SDL_SCANCODE_S] && grid.at((GetX() / 32 * 30 + GetY() / 32) + 1)->getIsMoveable())
		{
			SetY((GetY() + 32));
			inputDelay = SDL_GetTicks() + 200;
		}
		if (key[SDL_SCANCODE_A] && grid.at((GetX() / 32 * 30 + GetY() / 32) - 30)->getIsMoveable())
		{
			SetX((GetX() - 32));
			inputDelay = SDL_GetTicks() + 200;
		}
		if (key[SDL_SCANCODE_D] && grid.at((GetX() / 32 * 30 + GetY() / 32) + 30)->getIsMoveable())
		{
			SetX((GetX() + 32));
			inputDelay = SDL_GetTicks() + 200;
		}
	}
	SetCurrentNode();
}



void Player::Draw()
{
	Sprite::Draw();
}