#pragma once
#include <vector>

#include "StateTemplate.h"
#include "StateManager.h"
#include "Node.h"

class InGame : public StateTemplate
{
public:
	InGame(StateManager* _stateManager, std::vector<Node*> _grid, StateManager* _aiStateManager, StateManager* _bestFirstStateManager, StateManager* _aStarStateManager,SDL_Renderer* _renderer);
	~InGame();

	void Update();

	void Draw();
protected:
	SDL_Renderer* renderer;
	std::vector<Node*> grid;
	StateManager* breadthStateManager;
	StateManager* bestFirstManager;
	StateManager* aStarManager;
};