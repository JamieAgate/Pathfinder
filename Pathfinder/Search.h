#ifndef SEARCH_H
#define SEARCH_H
#include <algorithm>
#include <vector>

#include "StateTemplate.h"
#include "StateManager.h"
#include "AI.h"
#include "Node.h"
#include "Movement.h"

class Search : public StateTemplate
{
public:
	Search(StateManager* _stateManager, AIData* _agent);
	~Search();

	void Update();

	void SetStartNode(Node* _s) { start = _s; }
	void SetEndNode(Node* _e) { end = _e; }

	void ResetGrid();

	void BreadthSearch();
	void BestFirst();
	void AStarSearch();

	void Draw();
private:
	enum searchType { BREADTH, BEST, ASTAR };
	std::vector<Node*> path;
	Node* start;
	Node* end;
	bool pathFound;
	AIData* agent;
	void ReEvaluate(Node* _neighbour, Node* _node, std::vector <Node*> _vec, float cost);
};

#endif
