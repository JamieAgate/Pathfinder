#pragma once
#include "Sprite.h"
#include "Node.h"

class AIData {
public:
	AIData(int _searchType, std::vector<Node*> _grid, Sprite* _sprite);
	~AIData();

	void Update();
	
	int GetSearchType() { return searchType; }
	Node* GetStartNode() { return start; }
	Node* GetEndNode() { return end; }

	void SetPostitionInGridVector(int _g) { positionInGridVector = _g; }
	void SetStartNode(Node* _start) { start = _start; }
	void SetEndNode(Node* _end) { end = _end; }
	void SetPath(std::vector<Node*> _path) { path = _path; }

	void Move();

	void Draw();
protected:
	Node* start;
	Node* end;
	Sprite* image;
	enum e_searchType { BREADTH, BEST, ASTAR };
	int searchType;
	std::vector<Node*> grid;
	int positionInGridVector;
	std::vector<Node*> path;
};