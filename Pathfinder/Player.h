#pragma once
#include "Sprite.h"
#include "Node.h"
#include <vector>

class Player : public Sprite
{
public:
	Player(SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h, bool _canDeleteTex, std::vector<Node*> _grid);
	~Player();

	Node* GetCurrentOccupiedNode() { return currentNode; }

	void SetCurrentNode() { currentNode = grid.at(GetX() / 32 * 30 + GetY() / 32); }

	std::vector<Node*> GetGrid() { return grid; }

	void Update();

	void Draw();
private:
	int inputDelay;
	std::vector<Node*> grid;
	Node* currentNode;
};