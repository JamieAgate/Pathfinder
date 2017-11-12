#include "SetUp.h"

SetUp::SetUp(StateManager* _stateManager, StateManager* _aiManager, StateManager* _bestFirstStateManager, StateManager* _aStarStateManager, SDL_Renderer* _renderer) :
	StateTemplate(_stateManager)
{
	m_renderer = _renderer;

	SDL_Surface* bmp = IMG_Load("tile32.png");
	m_tile = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("Start.png");
	m_Start = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("End.png");
	m_End = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("Wall.png");
	m_Wall = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("m_Select.png");
	m_select = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("path.png");
	m_Path = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("Searched.png");
	m_searched = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("Astar.png");
	m_aStarTex = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("Best.png");
	m_bestTex = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("BreadthPath.png");
	m_breadthPath = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("BestPath.png");
	m_bestPath = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("AStarPath.png");
	m_aStarPath = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("HighCost.png");
	m_HighCost = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("MedCost.png");
	m_MedCost = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("LowCost.png");
	m_LowCost = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("Attack.png");
	m_Attack = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("Idle.png");
	m_Idle = SDL_CreateTextureFromSurface(_renderer, bmp);

	m_Select = new Cursor(_renderer, m_select, 0, 0, 32, 32);
	m_start = new Sprite(_renderer, m_Start, -32, -32, 32, 32,true);
	m_end = new Sprite(_renderer, m_End, -32, -32, 32, 32,true);
	m_bestSprite = new Sprite(_renderer, m_bestTex, -32, -32, 32, 32,true);
	m_aStarSprite = new Sprite(_renderer, m_aStarTex, -32, -32, 32, 32, true);
	m_breadthPathSprite = new Sprite(_renderer, m_breadthPath, -32, -32, 32, 32, true);
	m_bestFirstPathSprite = new Sprite(_renderer, m_bestPath, -32, -32, 32, 32, true);
	m_aStarPathSprite = new Sprite(_renderer, m_aStarPath, -32, -32, 32, 32, true);
	m_AttackSprite = new Sprite(_renderer, m_Attack, -32, -32, 32, 32, true);
	m_IdleSprite = new Sprite(_renderer, m_Idle, -32, -32, 32, 32, true);

	m_nodeCost = e_Wall;

	//make m_Grid
	for (int x = 0; x < m_GridWIDTH; x++)
	{
		for (int y = 0; y < m_GridHEIGHT; y++)
		{
			Node* newNode = new Node(_renderer, m_tile, x * 32, y * 32, 32, 32, x, y);
			m_Grid.push_back(newNode);
		}
	}

	bmp = IMG_Load("Start.png");
	SDL_Texture* m_playerTex = SDL_CreateTextureFromSurface(_renderer, bmp);
	m_player = new Player(_renderer, m_playerTex, 0, 0, 32, 32, true, m_Grid);

	SDL_FreeSurface(bmp);
	//make the neighbours
	int i = 0;
	for (int x = 0; x < m_GridWIDTH; x++) {
		for (int y = 0; y < m_GridHEIGHT; y++)
		{
			if (x == 0)
			{
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i + m_GridWIDTH));
			}
			else if (x == m_GridWIDTH - 1)
			{
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i - m_GridHEIGHT));
			}
			else
			{
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i + m_GridWIDTH));
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i - m_GridHEIGHT));
			}

			if (y == 0)
			{
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i + 1));
			}
			else if (y == m_GridHEIGHT - 1)
			{
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i - 1));
			}
			else
			{
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i + 1));
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i - 1));
			}
			//inner diagonals
			if (x != 0 && y != 0 && x != m_GridWIDTH - 1 && y != m_GridHEIGHT - 1)
			{
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i - m_GridWIDTH - 1));
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i - m_GridWIDTH + 1));
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i + m_GridWIDTH - 1));
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i + m_GridWIDTH + 1));
			}
			//edge diagonals
			if (x == 0 && y != 0 && y != m_GridHEIGHT - 1)
			{
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i + m_GridWIDTH - 1));
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i + m_GridWIDTH + 1));
			}
			if (y == 0 && x != 0 && x != m_GridWIDTH - 1)
			{
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i - m_GridWIDTH + 1));
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i + m_GridWIDTH + 1));
			}
			if (x == m_GridWIDTH - 1 && y != 0 && y != m_GridHEIGHT - 1)
			{
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i - m_GridWIDTH + 1));
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i - m_GridWIDTH - 1));
			}
			if (y == m_GridHEIGHT - 1 && x != 0 && x != m_GridWIDTH - 1)
			{
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i + m_GridWIDTH - 1));
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i - m_GridWIDTH - 1));
			}
			if (x == 0 && y == 0)//top left corner
			{
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i + m_GridWIDTH + 1));
			}
			if (x == 0 && y == m_GridHEIGHT - 1)//bottom left corner
			{
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i + m_GridWIDTH - 1));
			}
			if (x == m_GridWIDTH - 1 && y == 0)//top right corner
			{
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i - m_GridWIDTH + 1));
			}
			if (x == m_GridWIDTH - 1 && y == m_GridHEIGHT - 1)// bottom right corner
			{
				m_Grid.at(i)->SetNeighbours(m_Grid.at(i - m_GridWIDTH - 1));
			}
			i++;
		}
	}

	m_breadthStateManager = _aiManager;
	m_bestFirstManager = _bestFirstStateManager;
	m_aStarManager = _aStarStateManager;
	m_breadthFirstData = new AIData(BREADTH, m_Grid, m_end, m_breadthPath,m_renderer, m_player,m_AttackSprite,m_IdleSprite);
	m_bestFirstData = new AIData(BEST, m_Grid, m_bestSprite, m_bestPath, m_renderer, m_player, m_AttackSprite, m_IdleSprite);
	m_aStarData = new AIData(ASTAR, m_Grid, m_aStarSprite, m_aStarPath, m_renderer, m_player, m_AttackSprite, m_IdleSprite);
}

SetUp::~SetUp()
{
	for (size_t i = 0; i < m_Grid.size(); i++)
	{
		delete m_Grid.at(i);
	}
	m_Grid.clear();
	delete m_Select;
	delete m_start;
	delete m_end;
	delete m_StartNode;
	delete m_EndNode;
}

void SetUp::Update()
{
	m_Select->update();
	const Uint8* key = SDL_GetKeyboardState(NULL);


	m_currentNode = m_Select->getMouseX() / 32 * 30 + m_Select->getMouseY() / 32;

	//place m_player
	if (key[SDL_SCANCODE_S])
	{
		if (m_previousStartNode != m_currentNode)
		{
			m_Grid.at(m_previousStartNode)->setIsStart(false);
			m_Grid.at(m_previousStartNode)->setTexture(m_tile);
			m_previousStartNode = m_currentNode;
		}
		m_StartNode = m_Grid.at(m_currentNode);

		m_player->SetX((m_Select->getMouseX() / 32) * 32);
		m_player->SetY((m_Select->getMouseY() / 32) * 32);
		m_player->SetCurrentNode();

		m_breadthFirstData->SetStartNode(m_Grid.at(m_currentNode));
		m_bestFirstData->SetStartNode(m_Grid.at(m_currentNode));
		m_aStarData->SetStartNode(m_Grid.at(m_currentNode));

	}
	//place breadth first
	if (key[SDL_SCANCODE_Z])
	{
		if (m_previousEndNode != m_currentNode)
		{
			m_Grid.at(m_previousEndNode)->setIsGoal(false);
			m_previousEndNode = m_currentNode;
		}
		m_end->SetX(m_Grid.at(m_currentNode)->GetX());
		m_end->SetY(m_Grid.at(m_currentNode)->GetY());
		m_Grid.at(m_currentNode)->setIsGoal(true);
		m_breadthFirstData->SetEndNode(m_Grid.at(m_currentNode));
		m_breadthStateManager->AddState(new Idle(m_breadthStateManager, m_breadthFirstData));
	}
	//place best first
	if (key[SDL_SCANCODE_X])
	{
		if (m_previousBestFirstNode != m_currentNode)
		{
			m_Grid.at(m_previousBestFirstNode)->setIsGoal(false);
			m_previousBestFirstNode = m_currentNode;
		}
		m_bestSprite->SetX(m_Grid.at(m_currentNode)->GetX());
		m_bestSprite->SetY(m_Grid.at(m_currentNode)->GetY());
		m_Grid.at(m_currentNode)->setIsGoal(true);
		m_bestFirstData->SetEndNode(m_Grid.at(m_currentNode));
		m_bestFirstManager->AddState(new Idle(m_bestFirstManager, m_bestFirstData));
	}
	//place A star
	if (key[SDL_SCANCODE_C])
	{
		if (m_previousAStarNode != m_currentNode)
		{
			m_Grid.at(m_previousAStarNode)->setIsGoal(false);
			m_previousAStarNode = m_currentNode;
		}
		m_aStarSprite->SetX(m_Grid.at(m_currentNode)->GetX());
		m_aStarSprite->SetY(m_Grid.at(m_currentNode)->GetY());
		m_Grid.at(m_currentNode)->setIsGoal(true);
		m_aStarData->SetEndNode(m_Grid.at(m_currentNode));
		m_aStarManager->AddState(new Idle(m_aStarManager, m_aStarData));
	}

	//clear m_Grid
	if (key[SDL_SCANCODE_BACKSPACE])
	{
		for each(Node* _node in m_Grid)
		{
			_node->setTexture(m_tile);
			_node->setMoveable(true);
		}
	}
	//walls
	if (key[SDL_SCANCODE_1])
	{
		m_nodeCost = e_Wall;
	}
	if (key[SDL_SCANCODE_2])
	{
		m_nodeCost = e_High;
	}
	if (key[SDL_SCANCODE_3])
	{
		m_nodeCost = e_Med;
	}
	if (key[SDL_SCANCODE_4])
	{
		m_nodeCost = e_Low;
	}

	if (SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (key[SDL_SCANCODE_LCTRL])
		{
				m_Grid.at(m_currentNode)->setTexture(m_tile);
				m_Grid.at(m_currentNode)->SetNodeCost(0);
				m_Grid.at(m_currentNode)->setMoveable(true);

		}
		else
		{
			switch (m_nodeCost)
			{
			case(e_Wall):
			{
				m_Grid.at(m_currentNode)->setTexture(m_Wall);
				m_Grid.at(m_currentNode)->setMoveable(false);
				break;
			}
			case(e_High):
			{
				m_Grid.at(m_currentNode)->setTexture(m_HighCost);
				m_Grid.at(m_currentNode)->SetNodeCost(6);
				m_Grid.at(m_currentNode)->setMoveable(true);
				break;
			}
			case(e_Med):
			{
				m_Grid.at(m_currentNode)->setTexture(m_MedCost);
				m_Grid.at(m_currentNode)->SetNodeCost(4);
				m_Grid.at(m_currentNode)->setMoveable(true);
				break;
			}
			case(e_Low):
			{
				m_Grid.at(m_currentNode)->setTexture(m_LowCost);
				m_Grid.at(m_currentNode)->SetNodeCost(2);
				m_Grid.at(m_currentNode)->setMoveable(true);
				break;
			}
			}
		}
	}

	if (key[SDL_SCANCODE_RETURN])
	{
		if (m_breadthStateManager->GetSizeOfStateVector() != 0 && m_aStarManager->GetSizeOfStateVector() != 0 && m_bestFirstManager->GetSizeOfStateVector() != 0 && m_StartNode != nullptr)
		{
			stateManager->ChangeState(new InGame(stateManager, m_Grid, m_breadthStateManager,m_bestFirstManager,m_aStarManager,m_renderer,m_player));
		}
	}
}

void SetUp::Draw()
{
	for (size_t i = 0; i < m_Grid.size(); i++)
	{
		m_Grid.at(i)->Draw();
	}
	m_Select->Draw();
	m_start->Draw();
	m_end->Draw();
	m_bestSprite->Draw();
	m_aStarSprite->Draw();
	m_player->Draw();
}