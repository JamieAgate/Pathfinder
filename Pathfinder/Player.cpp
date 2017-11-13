/// @file Player.cpp
/// @brief The player and all their movements
#include "Player.h"

Player::Player( SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h, bool _canDeleteTex, std::vector<Node*> _grid ) :
	Sprite( _renderer, _tex, _x, _y, _w, _h, _canDeleteTex )
{
	m_inputDelay = SDL_GetTicks() + 200;//sets the input delay to be 0.2
	m_grid = _grid;//sets the grid
	m_currentNode = m_grid.at( _x / 32 * 30 + _y / 32 );//sets the current node
}

Player::~Player()
{

}

void Player::Update()
{
	const Uint8* key = SDL_GetKeyboardState( NULL );//get keyboard state
	if ( SDL_GetTicks() > m_inputDelay )//if the current time is greater than the input delay
	{
		if ( key[SDL_SCANCODE_W] && m_grid.at( (GetX() / 32 * 30 + GetY() / 32) - 1 )->getIsMoveable() )//if W is pressed and the node trying to be moved to is not a wall
		{
			SetY( (GetY() - 32) );//move the agent
			m_inputDelay = SDL_GetTicks() + 200;//reset the input delay
		}
		if ( key[SDL_SCANCODE_S] && m_grid.at( (GetX() / 32 * 30 + GetY() / 32) + 1 )->getIsMoveable() )//if S is pressed and the node trying to be moved to is not a wall
		{
			SetY( (GetY() + 32) );//move the agent
			m_inputDelay = SDL_GetTicks() + 200;//reset the input delay
		}
		if ( key[SDL_SCANCODE_A] && m_grid.at( (GetX() / 32 * 30 + GetY() / 32) - 30 )->getIsMoveable() )//if A is pressed and the node trying to be moved to is not a wall
		{
			SetX( (GetX() - 32) );//move the agent
			m_inputDelay = SDL_GetTicks() + 200;//reset the input delay
		}
		if ( key[SDL_SCANCODE_D] && m_grid.at( (GetX() / 32 * 30 + GetY() / 32) + 30 )->getIsMoveable() )//if D is pressed and the node trying to be moved to is not a wall
		{
			SetX( (GetX() + 32) );//move the agent
			m_inputDelay = SDL_GetTicks() + 200;//reset the input delay
		}
	}
	SetCurrentNode();//set the current node
}



void Player::Draw()
{
	Sprite::Draw();//draw the sprite
}