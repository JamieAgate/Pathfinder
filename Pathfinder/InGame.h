#pragma once
#include <vector>

#include "StateTemplate.h"
#include "StateManager.h"
#include "Node.h"

class InGame : public StateTemplate
{
public:
	InGame(StateManager* _stateManager, std::vector<Node*> _grid, StateManager* _aiStateManager);
	~InGame();

	void Update();

	void Draw();
protected:
	std::vector<Node*> grid;
	StateManager* aiStateManager;
};