#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "StateTemplate.h"
#include "StateManager.h"
#include "Node.h"
#include "Cursor.h"
#include "AI.h"
#include "Idle.h"
#include "InGame.h"

class SetUp : public StateTemplate
{
public:
	SetUp(StateManager* _stateManager,StateManager* _aiManager,SDL_Renderer* _renderer);
	~SetUp();

	void Update();

	void Draw();
protected:
	bool pathfound = false;
	SDL_Renderer* renderer;
	std::vector<Node*> Grid;
	int GridWIDTH = 30;
	int GridHEIGHT = 30;
	int previousStartNode = 0;
	int previousEndNode = 0;
	int currentNode = 0;
	enum Search { BREADTH, BEST, ASTAR };
	int searchType = BREADTH;

	SDL_Texture* tile;
	SDL_Texture* Start;
	SDL_Texture* End;
	SDL_Texture* Wall;
	SDL_Texture* select;
	SDL_Texture* Path;
	SDL_Texture* searched;

	Cursor* Select;
	Sprite* start;
	Sprite* end;
	Node* StartNode = nullptr;
	Node* EndNode = nullptr;
	Node* finished = nullptr;

	StateManager* aiStateManager;
	AIData* breadthFirstData;
};