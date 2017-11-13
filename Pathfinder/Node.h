/// \file Node.m_h
/// \brief Base node class.

#ifndef _NODE_H_
#define _NODE_H_
//File Includes
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <vector>
//Additional File Includes
#include "Sprite.h"

class Node : public Sprite {
public:
	Node(SDL_Renderer* _renderer, SDL_Texture* _tex, int _x, int _y, int _w, int _h, int _gridx,int _gridy);//Node Constuctor
	~Node();//Node Destructor

	int GetGridX() { return m_x; };//Get the X co-ordinaate of the Node In the Grid
	int getGridY() { return m_y; };//Get the Y co-ordinate of the Node in the Grid
	bool getIsGoal() { return m_isGoal; }//Get if the node is the goal node or not
	std::vector<Node*> getNeighbours() { return m_Neighbours; }//get all of the nodes neighbours
	Node* getParent() { return m_parent; }//get the Nodes Parent
	bool getIsMoveable() { return m_Moveable; }//Get if the node is Moveable(A Wall) or not
	bool getIsStart() { return m_isStart; }//Get if the Node is the start node
	double getH() { return m_h; }//Get the nodes H value
	double getG() { return m_g; }//Get the nodes G value
	double getF() { return m_f; }//Get the nodes H value
	int GetNodeCost() { return m_nodeCost; }//Get the cost of the node

	void setGridX(int _x) { m_x = _x; };//set the x co-ordinate of the node in the grid
	void setGridY(int _y) { m_y = _y; };//set the y co-ordinate of the node in the grid
	void setMoveable(bool _b) { m_Moveable = _b; }//set if the Node is Moveable(A Wall) or not
	void SetNeighbours(Node* _node);//Add a node to the Neighbours vector
	void setIsGoal(bool _b) { m_isGoal = _b; }//Set if the node is the goal
	void setParent(Node* _n) { m_parent = _n; }//get the parent node
	void setIsStart(bool _b) { m_isStart = _b; }//set if the node is the start
	void setH(double _h) { m_h = _h; }//set the H value
	void setG(double _g) { m_g = _g; }//set the G value
	void setF() { m_f = m_g+m_h; }//Set the F value
	void SetNodeCost(int _n) { m_nodeCost = _n; }//set the nodes cost

	void Draw();//Draw the Node
private:
	double m_h;//Distance from Node to Goal
	double m_g;//number of steps from start
	double m_f;//G+H
	int m_nodeCost;//cost to move to the Node
	std::vector <Node*> m_Neighbours;//all Neighbours of the node
	Node* m_parent;//the nodes parent
	int m_x;//the x co-ordinate in the grid
	int m_y;//the y co-ordinate in the grid
	bool m_Moveable;//if the node is moveable
	bool m_isGoal;//if the node is the goal
	bool m_isStart;//if the node is the start node
};
#endif // !_NODE_H_
