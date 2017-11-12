#include "Node.h"

Node::Node(SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h, int _gridx, int _gridy):
	Sprite(_renderer,_tex,_x,_y,_w,_h,true)
{
	x = _gridx;
	y = _gridy;
	Moveable = true;
	isGoal = false;
	isStart = false;
	parent = nullptr;
	f = 0;
	g = 0;
	h = 0;
	nodeCost = 0;
}

Node ::~Node()
{
	
}

void Node::SetNeighbours(Node* _node)
{
	Neighbours.push_back(_node);
}

void Node::Draw()
{
	Sprite::Draw();
}