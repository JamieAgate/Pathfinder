/// \file InGame.h
/// \brief Game State that will run when setting up the game.
#pragma once


//File Includes
#include <SDL.h>
#include <SDL_image.h>
//Additional File Includes
#include "StateTemplate.h"
#include "StateManager.h"
#include "Node.h"
#include "Cursor.h"
#include "AI.h"
#include "Idle.h"
#include "InGame.h"
#include "Player.h"

class SetUp : public StateTemplate
{
public:
	SetUp(StateManager* _stateManager,StateManager* _aiManager, StateManager* _bestFirstStateManager, StateManager* _aStarStateManager,SDL_Renderer* _renderer);//constructor of Setup
	~SetUp();//Destructer of SetUp

	void Update();//Update for SetUp

	void Draw();//Draw for SetUp
protected:
	SDL_Renderer* m_renderer;//renderer used by the state
	std::vector<Node*> m_Grid;//grid of nodes used by the ai
	int m_GridWIDTH = 30;//the grid width
	int m_GridHEIGHT = 30;//the grid height
	int m_previousStartNode = 0;//the location of the previous start node(Player) in the grid vector
	int m_previousEndNode = 0;// the location of the previous breadth first node in the vector
	int m_previousAStarNode = 0;//the location of the previous best first node in the vector
	int m_previousBestFirstNode = 0;// the location of the previous a* node in the vector
	int m_currentNode = 0;//location of the current node in the vector that the mouse is over
	enum Search { BREADTH, BEST, ASTAR };//Enum for the different search types
	int m_searchType = BREADTH;//search type used

	SDL_Texture* m_tile;//texture for a standard node
	SDL_Texture* m_Start;//texture for the player
	SDL_Texture* m_End;// texture for breadth first agent
	SDL_Texture* m_Wall;//texture for wall
	SDL_Texture* m_select;//texture for cursour
	SDL_Texture* m_aStarTex;// texture for the A* agent
	SDL_Texture* m_bestTex;//texture for the best first agent
	SDL_Texture* m_breadthPath;//texture for the breadth first path
	SDL_Texture* m_bestPath;//texture for the best first path
	SDL_Texture* m_aStarPath;//texture for the aStar path
	SDL_Texture* m_HighCost;//texture for the High cost node
	SDL_Texture* m_MedCost;//texture for the medium cost node
	SDL_Texture* m_LowCost;//texture for a low cost node
	SDL_Texture* m_Attack;//texture for agents atack state
	SDL_Texture* m_Idle;//texture for agents idle state

	enum WallCost {e_Wall,e_High,e_Med,e_Low};//enum for the differnet placeable nodes
	int m_nodeCost;//node type used

	Cursor* m_Select;//cursour
	Sprite* m_start;//player sprite
	Sprite* m_end;//breadth first sprite
	Sprite* m_bestSprite;//best first sprite
	Sprite* m_aStarSprite;//a star sprite
	Sprite* m_AttackSprite;//attack sprite
	Sprite* m_IdleSprite;//idle sprite

	Sprite* m_breadthPathSprite;//breadth first path sprite
	Sprite* m_bestFirstPathSprite;//best first path sprite
	Sprite* m_aStarPathSprite;//a* path sprite

	Player* m_player;//player 

	Node* m_StartNode = nullptr;//start node
	Node* m_EndNode = nullptr;//end node

	StateManager* m_breadthStateManager;//breadth first state manager
	StateManager* m_bestFirstManager;//best first state manager
	StateManager* m_aStarManager;//a* state manager
	AIData* m_breadthFirstData;//breadth first agent
	AIData* m_bestFirstData;//best first agent
	AIData* m_aStarData;//a* agent
};

