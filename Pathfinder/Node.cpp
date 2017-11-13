/// @file Node.cpp
/// @brief The base Node Class used to make the grid
#include "Node.h"

Node::Node( SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h, int _gridx, int _gridy ) :
	Sprite( _renderer, _tex, _x, _y, _w, _h, true )
{
	m_x = _gridx;//sets the x co-ordinate of the node on the grid
	m_y = _gridy;//sets the y co-ordinate of the node on the grid
	m_Moveable = true;//sets the node to be moveable by default
	m_isGoal = false;//sets the node to not be the goal
	m_isStart = false;//sets the node to not be the start
	m_parent = nullptr;//sets it to have no parent
	m_f = 0;//sets f to 0
	m_g = 0;//sets g to 0
	m_h = 0;//sets h to 0
	m_nodeCost = 0;//sets the defualt cost of node to 0
}

Node ::~Node()
{

}

void Node::SetNeighbours( Node* _node )
{
	m_Neighbours.push_back( _node );//adds a node to the neighbours vector
}

void Node::Draw()
{
	Sprite::Draw();//draws the node
}