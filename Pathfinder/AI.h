#pragma once
#include "Sprite.h"
#include "Node.h"
#include "Player.h"

class AIData {
public:
	AIData(int _searchType, std::vector<Node*> _grid, Sprite* _sprite, SDL_Texture* _pathSprite,SDL_Renderer* _renderer, Player* _player,Sprite* _attack, Sprite* _Idle);
	~AIData();

	void Update();
	
	int GetSearchType() { return searchType; }
	Node* GetStartNode() { return start; }
	Node* GetEndNode() { return end; }
	int GetDrawnathSize() { return drawnPath.size(); }
	int GetPathSize() { return path.size(); }
	Node* GetPathEndNode() { return player->GetCurrentOccupiedNode(); }
	Node* GetCurrentOccupiedNode() { return grid.at(image->GetX() / 32 * 30 + image->GetY() / 32); }
	int GetSizeOfPath() { return sizeOfPath; }
	int GetCurrentSizeOfPath() { return path.size(); }
	std::vector<Node*> GetGrid() { return player->GetGrid(); }
	int GetDistanceForPlayer();


	void SetPostitionInGridVector(int _g) { positionInGridVector = _g; }
	void SetStartNode(Node* _start) { start = _start; }
	void SetEndNode(Node* _end) { end = _end; }
	void SetPath(std::vector<Node*> _path) { path.clear(); path = _path; }
	void SetSizeOfPath(int _n) { sizeOfPath = _n; }

	void Move();
	void MakeDrawPath();

	void Draw();
	void DrawAttack();
	void DrawIdle();
	void DrawPath();
protected:
	Player* player;
	SDL_Renderer* renderer;
	Node* start;
	Node* end;
	Sprite* image;
	Sprite* attack;
	Sprite* idle;
	SDL_Texture* pathSprite;
	enum e_searchType { BREADTH, BEST, ASTAR };
	int searchType;
	std::vector<Node*> grid;
	int positionInGridVector;
	std::vector<Node*> path;
	std::vector<Sprite*> drawnPath;
	int sizeOfPath;
};