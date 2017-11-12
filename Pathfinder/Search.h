/// \file Search.h
/// \brief AI state that will be used when the AI is Searching.

#ifndef SEARCH_H
#define SEARCH_H
//File Includes
#include <algorithm>
#include <vector>
//Additional File Includes
#include "StateTemplate.h"
#include "StateManager.h"
#include "AI.h"
#include "Node.h"
#include "Movement.h"

class Search : public StateTemplate
{
public:
	Search(StateManager* _stateManager, AIData* _agent);//Search Constructor
	~Search();//Search destructor

	void Update();//Search Update

	void SetStartNode(Node* _s) { m_start = _s; }//Set the searching start node
	void SetEndNode(Node* _e) { m_end = _e; }//Set the searching end node

	void ResetGrid();//Reset all values of nodes on grid

	void BreadthSearch();//breadth first search algorithm
	void BestFirst();//best first search algorithm
	void AStarSearch();//a* search algorithm

	void Draw();//Search Draw
private:
	enum searchType { BREADTH, BEST, ASTAR };//enum for algorithm used
	std::vector<Node*> m_path;//the vector of all Nodes in the found path
	Node* m_start;//node at the start of the search
	Node* m_end;//node at the end of the search
	bool m_pathFound;//bool for if the path has been found or not
	AIData* m_agent;//The AI agent
	void ReEvaluate(Node* _neighbour, Node* _node, std::vector <Node*> _vec, float cost);//function to Re-Evaluate the parent of a node
};

#endif
