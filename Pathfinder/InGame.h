/// \file InGame.h
/// \brief Game State that will run when in Game.
#pragma once


//File includes
#include <vector>
//Additional File Includes
#include "StateTemplate.h"
#include "StateManager.h"
#include "Node.h"
#include "Player.h"
#include "SetUp.h"
//Header Contents
class InGame : public StateTemplate
{
public:
	InGame(StateManager* _stateManager, std::vector<Node*> _grid, StateManager* _aiStateManager, StateManager* _bestFirstStateManager, StateManager* _aStarStateManager,SDL_Renderer* _renderer, Player* _player); //Constructor for InGame
	~InGame();//Destructor for InGame

	void Update();//Update function for InGame

	void Draw();//Draw function for InGame
protected:
	SDL_Renderer* m_renderer;//Game renderer that everything will draw to
	std::vector<Node*> m_grid;//The Grid of nodes that the AI is based on
	StateManager* m_breadthStateManager;//The State Manager for the Breadth-First AI
	StateManager* m_bestFirstManager;//The State Manager for the Best-First AI
	StateManager* m_aStarManager;//The State Manager for the A* AI
	Player* m_player;//The Player
};


