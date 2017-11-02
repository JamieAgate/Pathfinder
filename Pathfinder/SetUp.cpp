#include "SetUp.h"

SetUp::SetUp(StateManager* _stateManager, StateManager* _aiManager, SDL_Renderer* _renderer) :
	StateTemplate(_stateManager)
{
	renderer = _renderer;

	SDL_Surface* bmp = IMG_Load("tile32.png");
	tile = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("Start.png");
	Start = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("End.png");
	End = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("Wall.png");
	Wall = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("Select.png");
	select = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("path.png");
	Path = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("Searched.png");
	searched = SDL_CreateTextureFromSurface(_renderer, bmp);

	SDL_FreeSurface(bmp);

	Select = new Cursor(_renderer, select, 0, 0, 32, 32);
	start = new Sprite(_renderer, Start, -32, -32, 32, 32);
	end = new Sprite(_renderer, End, -32, -32, 32, 32);

	//make Grid
	for (int x = 0; x < GridWIDTH; x++)
	{
		for (int y = 0; y < GridHEIGHT; y++)
		{
			Node* newNode = new Node(_renderer, tile, x * 32, y * 32, 32, 32, x, y);
			Grid.push_back(newNode);
		}
	}

	//make the neighbours
	int i = 0;
	for (int x = 0; x < GridWIDTH; x++) {
		for (int y = 0; y < GridHEIGHT; y++)
		{
			if (x == 0)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH));
			}
			else if (x == GridWIDTH - 1)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i - GridHEIGHT));
			}
			else
			{
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH));
				Grid.at(i)->SetNeighbours(Grid.at(i - GridHEIGHT));
			}

			if (y == 0)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i + 1));
			}
			else if (y == GridHEIGHT - 1)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i - 1));
			}
			else
			{
				Grid.at(i)->SetNeighbours(Grid.at(i + 1));
				Grid.at(i)->SetNeighbours(Grid.at(i - 1));
			}
			if (x != 0 && y != 0 && x != GridWIDTH - 1 && y != GridHEIGHT - 1)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH - 1));
				Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH + 1));
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH - 1));
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH + 1));
			}
			//edge diagonals
			if (x == 0 && y != 0 && y != GridHEIGHT - 1)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH - 1));
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH + 1));
			}
			if (y == 0 && x != 0 && x != GridWIDTH - 1)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH + 1));
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH + 1));
			}
			if (x == GridWIDTH - 1 && y != 0 && y != GridHEIGHT - 1)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH + 1));
				Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH - 1));
			}
			if (y == GridHEIGHT - 1 && x != 0 && x != GridWIDTH - 1)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH - 1));
				Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH - 1));
			}
			if (x == 0 && y == 0)//top left corner
			{
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH + 1));
			}
			if (x == 0 && y == GridHEIGHT - 1)//bottom left corner
			{
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH - 1));
			}
			if (x == GridWIDTH - 1 && y == 0)//top right corner
			{
				Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH + 1));
			}
			if (x == GridWIDTH - 1 && y == GridHEIGHT - 1)// bottom right corner
			{
				Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH - 1));
			}
			i++;
		}
	}

	aiStateManager = _aiManager;
	breadthFirstData = new AIData(BREADTH, Grid, end);
}

SetUp::~SetUp()
{
	for (size_t i = 0; i < Grid.size(); i++)
	{
		delete Grid.at(i);
	}
	Grid.clear();
	delete Select;
	delete start;
	delete end;
	delete StartNode;
	delete EndNode;
}

void SetUp::Update()
{
	Select->update();
	const Uint8* key = SDL_GetKeyboardState(NULL);


	currentNode = Select->getMouseX() / 32 * 30 + Select->getMouseY() / 32;

	//place start node
	if (key[SDL_SCANCODE_S])
	{
		if (previousStartNode != currentNode)
		{
			Grid.at(previousStartNode)->setIsStart(false);
			previousStartNode = currentNode;
		}
		start->SetX(Grid.at(currentNode)->GetX());
		start->SetY(Grid.at(currentNode)->GetY());
		Grid.at(currentNode)->setIsStart(true);
		breadthFirstData->SetStartNode(Grid.at(currentNode));
	}
	//place end node
	if (key[SDL_SCANCODE_E])
	{
		if (previousEndNode != currentNode)
		{
			Grid.at(previousEndNode)->setIsGoal(false);
			previousEndNode = currentNode;
		}
		end->SetX(Grid.at(currentNode)->GetX());
		end->SetY(Grid.at(currentNode)->GetY());
		Grid.at(currentNode)->setIsGoal(true);
		breadthFirstData->SetEndNode(Grid.at(currentNode));
	}
	//clear grid
	if (key[SDL_SCANCODE_BACKSPACE])
	{
		for each(Node* _node in Grid)
		{
			_node->setTexture(tile);
			_node->setMoveable(true);
		}
	}
	//
	if (SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (key[SDL_SCANCODE_LCTRL])
		{
			Grid.at(currentNode)->setTexture(tile);
			Grid.at(currentNode)->setMoveable(true);
		}
		else
		{
			Grid.at(currentNode)->setTexture(Wall);
			Grid.at(currentNode)->setMoveable(false);
		}
	}

	if (key[SDL_SCANCODE_1])
	{
		aiStateManager->ChangeState(new Idle(aiStateManager, breadthFirstData));
		searchType = BREADTH;
	}

	if (key[SDL_SCANCODE_3])
	{
		searchType = ASTAR;
	}

	if (key[SDL_SCANCODE_2])
	{
		searchType = BEST;
	}

	if (key[SDL_SCANCODE_RETURN])
	{
		stateManager->ChangeState(new InGame(stateManager, Grid, aiStateManager));
	//	pathfound = false;
	//	for (size_t i = 0; i < Grid.size(); i++)
	//	{
	//		if (!Grid.at(i)->getIsGoal() && !Grid.at(i)->getIsStart() && Grid.at(i)->getIsMoveable())
	//		{
	//			Grid.at(i)->setTexture(tile);
	//		}
	//	}
	//	switch (searchType)
	//	{
	//	case(BREADTH):
	//	{
	//		//finished = BreadthSearch(StartNode, EndNode, pathfound, searched);
	//		aiStateManager.Update();
	//		break;
	//	}
	//	case(ASTAR):
	//	{
	//		//ResetAllNodes(Grid);
	//		//finished = AStarSearch(StartNode, EndNode, pathfound, searched);
	//		break;
	//	}
	//	case(BEST):
	//	{
	//		//ResetAllNodes(Grid);
	//		//finished = BestFirst(StartNode, EndNode, pathfound, searched);
	//		break;
	//	}
	//	}
	}

}

void SetUp::Draw()
{
	for (size_t i = 0; i < Grid.size(); i++)
	{
		Grid.at(i)->Draw();
	}
	Select->Draw();
	start->Draw();
	end->Draw();
}