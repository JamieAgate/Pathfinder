#pragma once
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <vector>

#include "Sprite.h"

class Node : public Sprite {
public:
	Node(SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h, int _gridx,int _gridy);
	~Node();

	int GetGridX() { return x; };
	int getGridY() { return y; };
	bool getIsGoal() { return isGoal; }
	std::vector<Node*> getNeighbours() { return Neighbours; }
	Node* getParent() { return parent; }
	bool getIsMoveable() { return Moveable; }
	bool getIsStart() { return isStart; }
	double getH() { return h; }
	double getG() { return g; }
	double getF() { return f; }
	int GetNodeCost() { return nodeCost; }

	void setGridX(int _x) { x = _x; };
	void setGridY(int _y) { y = _y; };
	void setMoveable(bool _b) { Moveable = _b; }
	void SetNeighbours(Node* _node);
	void setIsGoal(bool _b) { isGoal = _b; }
	void setParent(Node* _n) { parent = _n; }
	void setIsStart(bool _b) { isStart = _b; }
	void setH(double _h) { h = _h; }
	void setG(double _g) { g = _g; }
	void setF() { f = g+h; }
	void SetNodeCost(int _n) { nodeCost = _n; }

	void Draw();
private:
	double h;
	double g;
	double f;
	int nodeCost;
	std::vector <Node*> Neighbours;
	Node* parent;
	int x;
	int y;
	bool Moveable;
	bool isGoal;
	bool isStart;
};