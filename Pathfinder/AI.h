#pragma once
#include "Sprite.h"
#include "Node.h"

class AIData {
public:
	AIData(int _searchType, std::vector<Node*> _grid, Sprite* _sprite, SDL_Texture* _pathSprite,SDL_Renderer* _renderer);
	~AIData();

	void Update();
	
	int GetSearchType() { return searchType; }
	Node* GetStartNode() { return start; }
	Node* GetEndNode() { return end; }
	int GetDrawnathSize() { return drawnPath.size(); }


	void SetPostitionInGridVector(int _g) { positionInGridVector = _g; }
	void SetStartNode(Node* _start) { start = _start; }
	void SetEndNode(Node* _end) { end = _end; }
	void SetPath(std::vector<Node*> _path) { path = _path; }

	void Move();

	void Draw();
	void MakeDrawPath();
	void DrawPath();
protected:
	SDL_Renderer* renderer;
	Node* start;
	Node* end;
	Sprite* image;
	SDL_Texture* pathSprite;
	enum e_searchType { BREADTH, BEST, ASTAR };
	int searchType;
	std::vector<Node*> grid;
	int positionInGridVector;
	std::vector<Node*> path;
	std::vector<Sprite*> drawnPath;
};