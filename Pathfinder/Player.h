/// \file Player.h
/// \brief Used to control the player during the game.

#ifndef _PLAYER_H_
#define _PLAYER_H_
//File Includes
#include <vector>
//Additional File Includes
#include "Sprite.h"
#include "Node.h"

class Player : public Sprite
{
public:
	Player(SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h, bool _canDeleteTex, std::vector<Node*> _grid);//Player Constructor
	~Player();//Player Destructor

	Node* GetCurrentOccupiedNode() { return m_currentNode; }//Get the Node player is currently on

	void SetCurrentNode() { m_currentNode = m_grid.at(GetX() / 32 * 30 + GetY() / 32); }//Set the Node the Player is currently on

	std::vector<Node*> GetGrid() { return m_grid; }//get the Grid

	void Update();//Update the player

	void Draw();//Draw the player
private:
	int m_inputDelay;//delay between input
	std::vector<Node*> m_grid;//grid of nodes
	Node* m_currentNode;//current Node the player is on
};

#endif // !_PLAYER_H_
