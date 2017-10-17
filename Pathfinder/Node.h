#pragma once
#include "Sprite.h"
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <vector>

class Node : public Sprite {
public:
	Node(SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h, int _gridx,int _gridy);
	~Node();

	int GetGridX() { return x; };
	int getGridY() { return y; };
	bool getIsGoal() { return isGoal; }
	std::vector<Node*> getNeighbours() { return Neighbours; }
	Node* getParent() { return parent; }
	bool getSearched() { return searched; }
	bool getIsMoveable() { return Moveable; }
	bool getIsStart() { return isStart; }
	float getH() { return h; }
	float getG() { return g; }
	float getF() { return f; }


	void setGridX(int _x) { x = _x; };
	void setGridY(int _y) { y = _y; };
	void setMoveable(bool _b) { Moveable = _b; }
	void SetNeighbours(Node* _node);
	void setIsGoal(bool _b) { isGoal = _b; }
	void setParent(Node* _n) { parent = _n; }
	void setSearched(bool _b) { searched = _b; }
	void setIsStart(bool _b) { isStart = _b; }
	void setH(float _h) { h = _h; }
	void setG(float _g) { g = _g; }
	void setF() { f = g+h; }

	void Draw();
private:
	float h;
	float g;
	float f;
	std::vector <Node*> Neighbours;
	Node* parent;
	bool searched;
	int x;
	int y;
	bool Moveable;
	bool isGoal;
	bool isStart;
};