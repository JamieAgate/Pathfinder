#include "InGame.h"

InGame::InGame(StateManager* _stateManager, std::vector<Node*> _grid, StateManager* _aiStateManager) :
	StateTemplate(_stateManager)
{
	grid = _grid;
	aiStateManager = _aiStateManager;
}

InGame::~InGame()
{

}

void InGame::Update()
{
	aiStateManager->Update();
}

void InGame::Draw()
{
	for (size_t i = 0; i < grid.size(); i++)
	{
		grid.at(i)->Draw();
	}
	aiStateManager->Draw();
}