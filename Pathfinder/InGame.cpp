#include "InGame.h"

InGame::InGame(StateManager* _stateManager, std::vector<Node*> _grid, StateManager* _breadthStateManager,StateManager* _bestFirstStateManager, StateManager* _aStarStateManager, SDL_Renderer* _renderer, Player* _player) :
	StateTemplate(_stateManager)
{
	renderer = _renderer;

	grid = _grid;
	breadthStateManager = _breadthStateManager;
	bestFirstManager = _bestFirstStateManager;
	aStarManager = _aStarStateManager;

	player = _player;
}

InGame::~InGame()
{

}

void InGame::Update()
{
	breadthStateManager->Update();
	bestFirstManager->Update();
	aStarManager->Update();

	player->Update();
}

void InGame::Draw()
{
	for (size_t i = 0; i < grid.size(); i++)
	{
		grid.at(i)->Draw();
	}
	breadthStateManager->Draw();
	bestFirstManager->Draw();
	aStarManager->Draw();
	player->Draw();
}