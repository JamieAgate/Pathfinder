#include "SetUp.h"

SetUp::SetUp(StateManager* _stateManager, StateManager* _aiManager, StateManager* _bestFirstStateManager, StateManager* _aStarStateManager, SDL_Renderer* _renderer) :
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

	bmp = IMG_Load("Astar.png");
	aStarTex = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("Best.png");
	bestTex = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("BreadthPath.png");
	breadthPath = SDL_CreateTextureFromSurface(renderer, bmp);

	bmp = IMG_Load("BestPath.png");
	bestPath = SDL_CreateTextureFromSurface(renderer, bmp);

	bmp = IMG_Load("AStarPath.png");
	aStarPath = SDL_CreateTextureFromSurface(renderer, bmp);



	Select = new Cursor(_renderer, select, 0, 0, 32, 32);
	start = new Sprite(_renderer, Start, -32, -32, 32, 32,true);
	end = new Sprite(_renderer, End, -32, -32, 32, 32,true);
	bestSprite = new Sprite(_renderer, bestTex, -32, -32, 32, 32,true);
	aStarSprite = new Sprite(_renderer, aStarTex, -32, -32, 32, 32, true);
	breadthPathSprite = new Sprite(_renderer, breadthPath, -32, -32, 32, 32, true);
	bestFirstPathSprite = new Sprite(_renderer, bestPath, -32, -32, 32, 32, true);
	aStarPathSprite = new Sprite(_renderer,	aStarPath, -32, -32, 32, 32, true);

	//make Grid
	for (int x = 0; x < GridWIDTH; x++)
	{
		for (int y = 0; y < GridHEIGHT; y++)
		{
			Node* newNode = new Node(_renderer, tile, x * 32, y * 32, 32, 32, x, y);
			Grid.push_back(newNode);
		}
	}

	bmp = IMG_Load("Start.png");
	SDL_Texture* playerTex = SDL_CreateTextureFromSurface(_renderer, bmp);
	player = new Player(_renderer, playerTex, 0, 0, 32, 32, true, Grid);

	SDL_FreeSurface(bmp);
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
			//inner diagonals
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

	breadthStateManager = _aiManager;
	bestFirstManager = _bestFirstStateManager;
	aStarManager = _aStarStateManager;
	breadthFirstData = new AIData(BREADTH, Grid, end,breadthPath,renderer,player);
	bestFirstData = new AIData(BEST, Grid, bestSprite,bestPath, renderer,player);
	aStarData = new AIData(ASTAR, Grid, aStarSprite,aStarPath, renderer,player);
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

	//place Player
	if (key[SDL_SCANCODE_S])
	{
		if (previousStartNode != currentNode)
		{
			Grid.at(previousStartNode)->setIsStart(false);
			Grid.at(previousStartNode)->setTexture(tile);
			previousStartNode = currentNode;
		}
		//start->SetX(Grid.at(currentNode)->GetX());
		//start->SetY(Grid.at(currentNode)->GetY());
		//Grid.at(currentNode)->setIsStart(true);
		//Grid.at(currentNode)->setTexture(Start);
		StartNode = Grid.at(currentNode);

		player->SetX((Select->getMouseX() / 32) * 32);
		player->SetY((Select->getMouseY() / 32) * 32);
		player->SetCurrentNode();

		breadthFirstData->SetStartNode(Grid.at(currentNode));
		bestFirstData->SetStartNode(Grid.at(currentNode));
		aStarData->SetStartNode(Grid.at(currentNode));

	}
	//place breadth first
	if (key[SDL_SCANCODE_Z])
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
		breadthStateManager->AddState(new Idle(breadthStateManager, breadthFirstData));
	}
	//place best first
	if (key[SDL_SCANCODE_X])
	{
		if (previousBestFirstNode != currentNode)
		{
			Grid.at(previousBestFirstNode)->setIsGoal(false);
			previousBestFirstNode = currentNode;
		}
		bestSprite->SetX(Grid.at(currentNode)->GetX());
		bestSprite->SetY(Grid.at(currentNode)->GetY());
		Grid.at(currentNode)->setIsGoal(true);
		bestFirstData->SetEndNode(Grid.at(currentNode));
		bestFirstManager->AddState(new Idle(bestFirstManager, bestFirstData));
	}
	//place A star
	if (key[SDL_SCANCODE_C])
	{
		if (previousAStarNode != currentNode)
		{
			Grid.at(previousAStarNode)->setIsGoal(false);
			previousAStarNode = currentNode;
		}
		aStarSprite->SetX(Grid.at(currentNode)->GetX());
		aStarSprite->SetY(Grid.at(currentNode)->GetY());
		Grid.at(currentNode)->setIsGoal(true);
		aStarData->SetEndNode(Grid.at(currentNode));
		aStarManager->AddState(new Idle(aStarManager, aStarData));
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
	//walls
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

	if (key[SDL_SCANCODE_RETURN])
	{
		if (breadthStateManager->GetSizeOfStateVector() != 0 && aStarManager->GetSizeOfStateVector() != 0 && bestFirstManager->GetSizeOfStateVector() != 0 && StartNode != nullptr)
		{
			stateManager->ChangeState(new InGame(stateManager, Grid, breadthStateManager,bestFirstManager,aStarManager,renderer,player));
		}
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
	bestSprite->Draw();
	aStarSprite->Draw();
	player->Draw();
}