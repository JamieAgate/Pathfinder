/// @file SetUp.cpp
/// @brief Sets up all agents and player for the game
#include "SetUp.h"

SetUp::SetUp( StateManager* _stateManager, StateManager* _aiManager, StateManager* _bestFirstStateManager, StateManager* _aStarStateManager, SDL_Renderer* _renderer ) :
	StateTemplate( _stateManager )
{
	m_renderer = _renderer;//set the renderer

	//LOAD ALL IMAGES NEEDED
	SDL_Surface* bmp = IMG_Load( "tile32.png" );
	m_tile = SDL_CreateTextureFromSurface( _renderer, bmp );

	bmp = IMG_Load( "Start.png" );
	m_Start = SDL_CreateTextureFromSurface( _renderer, bmp );

	bmp = IMG_Load( "End.png" );
	m_End = SDL_CreateTextureFromSurface( _renderer, bmp );

	bmp = IMG_Load( "Wall.png" );
	m_Wall = SDL_CreateTextureFromSurface( _renderer, bmp );

	bmp = IMG_Load( "m_Select.png" );
	m_select = SDL_CreateTextureFromSurface( _renderer, bmp );

	bmp = IMG_Load( "Astar.png" );
	m_aStarTex = SDL_CreateTextureFromSurface( _renderer, bmp );

	bmp = IMG_Load( "Best.png" );
	m_bestTex = SDL_CreateTextureFromSurface( _renderer, bmp );

	bmp = IMG_Load( "BreadthPath.png" );
	m_breadthPath = SDL_CreateTextureFromSurface( _renderer, bmp );

	bmp = IMG_Load( "BestPath.png" );
	m_bestPath = SDL_CreateTextureFromSurface( _renderer, bmp );

	bmp = IMG_Load( "AStarPath.png" );
	m_aStarPath = SDL_CreateTextureFromSurface( _renderer, bmp );

	bmp = IMG_Load( "HighCost.png" );
	m_HighCost = SDL_CreateTextureFromSurface( _renderer, bmp );

	bmp = IMG_Load( "MedCost.png" );
	m_MedCost = SDL_CreateTextureFromSurface( _renderer, bmp );

	bmp = IMG_Load( "LowCost.png" );
	m_LowCost = SDL_CreateTextureFromSurface( _renderer, bmp );

	bmp = IMG_Load( "Attack.png" );
	m_Attack = SDL_CreateTextureFromSurface( _renderer, bmp );

	bmp = IMG_Load( "Idle.png" );
	m_Idle = SDL_CreateTextureFromSurface( _renderer, bmp );

	SDL_FreeSurface( bmp );
	//FINISH LOADING ALL IMAGES

	//MAKE GRID
	for ( int x = 0; x < m_GridWIDTH; x++ )
	{
		for ( int y = 0; y < m_GridHEIGHT; y++ )
		{
			Node* newNode = new Node( _renderer, m_tile, x * 32, y * 32, 32, 32, x, y );
			m_Grid.push_back( newNode );
		}
	}
	//FINISH MAKING GRID

	//MAKE NEIGHBOURS
	int i = 0;
	for ( int x = 0; x < m_GridWIDTH; x++ )
	{
		for ( int y = 0; y < m_GridHEIGHT; y++ )
		{
			//vertical and horizontal neighbours
			if ( x == 0 )//On Left most side
			{
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i + m_GridWIDTH ) );
			}
			else if ( x == m_GridWIDTH - 1 )//on Right most side
			{
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i - m_GridHEIGHT ) );
			}
			else//in the middle
			{
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i + m_GridWIDTH ) );
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i - m_GridHEIGHT ) );
			}

			if ( y == 0 )//At top
			{
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i + 1 ) );
			}
			else if ( y == m_GridHEIGHT - 1 )//At bottom
			{
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i - 1 ) );
			}
			else//in middle
			{
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i + 1 ) );
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i - 1 ) );
			}
			//inner diagonals
			if ( x != 0 && y != 0 && x != m_GridWIDTH - 1 && y != m_GridHEIGHT - 1 )
			{
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i - m_GridWIDTH - 1 ) );
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i - m_GridWIDTH + 1 ) );
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i + m_GridWIDTH - 1 ) );
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i + m_GridWIDTH + 1 ) );
			}
			//edge diagonals
			if ( x == 0 && y != 0 && y != m_GridHEIGHT - 1 )//diagonals on left side nodes
			{
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i + m_GridWIDTH - 1 ) );
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i + m_GridWIDTH + 1 ) );
			}
			if ( y == 0 && x != 0 && x != m_GridWIDTH - 1 )//diagonals on top side nodes
			{
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i - m_GridWIDTH + 1 ) );
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i + m_GridWIDTH + 1 ) );
			}
			if ( x == m_GridWIDTH - 1 && y != 0 && y != m_GridHEIGHT - 1 )//diagonals on right side nodes
			{
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i - m_GridWIDTH + 1 ) );
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i - m_GridWIDTH - 1 ) );
			}
			if ( y == m_GridHEIGHT - 1 && x != 0 && x != m_GridWIDTH - 1 )//diagonals on bottom side nodes
			{
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i + m_GridWIDTH - 1 ) );
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i - m_GridWIDTH - 1 ) );
			}
			if ( x == 0 && y == 0 )//top left corner
			{
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i + m_GridWIDTH + 1 ) );
			}
			if ( x == 0 && y == m_GridHEIGHT - 1 )//bottom left corner
			{
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i + m_GridWIDTH - 1 ) );
			}
			if ( x == m_GridWIDTH - 1 && y == 0 )//top right corner
			{
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i - m_GridWIDTH + 1 ) );
			}
			if ( x == m_GridWIDTH - 1 && y == m_GridHEIGHT - 1 )// bottom right corner
			{
				m_Grid.at( i )->SetNeighbours( m_Grid.at( i - m_GridWIDTH - 1 ) );
			}
			i++;
		}
	}
	//FINSH MAKING NEIGHBOURS

	//CREATE ALL GAME OBJECTS
	m_Select = new Cursor( _renderer, m_select, 0, 0, 32, 32 );
	m_start = new Sprite( _renderer, m_Start, -32, -32, 32, 32, true );
	m_end = new Sprite( _renderer, m_End, -32, -32, 32, 32, true );
	m_bestSprite = new Sprite( _renderer, m_bestTex, -32, -32, 32, 32, true );
	m_aStarSprite = new Sprite( _renderer, m_aStarTex, -32, -32, 32, 32, true );
	m_breadthPathSprite = new Sprite( _renderer, m_breadthPath, -32, -32, 32, 32, true );
	m_bestFirstPathSprite = new Sprite( _renderer, m_bestPath, -32, -32, 32, 32, true );
	m_aStarPathSprite = new Sprite( _renderer, m_aStarPath, -32, -32, 32, 32, true );
	m_AttackSprite = new Sprite( _renderer, m_Attack, -32, -32, 32, 32, true );
	m_IdleSprite = new Sprite( _renderer, m_Idle, -32, -32, 32, 32, true );
	m_player = new Player( _renderer, m_Start, 0, 0, 32, 32, true, m_Grid );
	//FINISH CREATING GAME OBJECTS

	//default node cost drawn
	m_nodeCost = e_Wall;


	//Set AI Managers
	m_breadthStateManager = _aiManager;
	m_bestFirstManager = _bestFirstStateManager;
	m_aStarManager = _aStarStateManager;
	//Make AI Agents
	m_breadthFirstData = new AIData( BREADTH, m_Grid, m_end, m_breadthPath, m_renderer, m_player, m_AttackSprite, m_IdleSprite );
	m_bestFirstData = new AIData( BEST, m_Grid, m_bestSprite, m_bestPath, m_renderer, m_player, m_AttackSprite, m_IdleSprite );
	m_aStarData = new AIData( ASTAR, m_Grid, m_aStarSprite, m_aStarPath, m_renderer, m_player, m_AttackSprite, m_IdleSprite );
}

SetUp::~SetUp()
{
	for ( size_t i = 0; i < m_Grid.size(); i++ )//delete grid
	{
		delete m_Grid.at( i );
	}
	m_Grid.clear();//clear vector
	delete m_Select;//delete cursour
	delete m_start;//delete start
	delete m_end;//delete end
	delete m_StartNode;//delete start node
	delete m_EndNode;//delete end node
}

void SetUp::Update()
{
	m_Select->Update();//update the cursour
	const Uint8* key = SDL_GetKeyboardState( NULL );//get the keyboard state

	m_currentNode = m_Select->getMouseX() / 32 * 30 + m_Select->getMouseY() / 32;//calculate the node that the mouse is over

	//place player
	if ( key[SDL_SCANCODE_S] )//if S is pressed
	{
		if ( m_previousStartNode != m_currentNode )//reset the previous node
		{
			m_Grid.at( m_previousStartNode )->setIsStart( false );
			m_Grid.at( m_previousStartNode )->setTexture( m_tile );
			m_previousStartNode = m_currentNode;
		}
		//set up the new start
		m_StartNode = m_Grid.at( m_currentNode );
		//move players position
		m_player->SetX( (m_Select->getMouseX() / 32) * 32 );
		m_player->SetY( (m_Select->getMouseY() / 32) * 32 );
		m_player->SetCurrentNode();
		//set all agents Start node to be Players node
		m_breadthFirstData->SetStartNode( m_Grid.at( m_currentNode ) );
		m_bestFirstData->SetStartNode( m_Grid.at( m_currentNode ) );
		m_aStarData->SetStartNode( m_Grid.at( m_currentNode ) );

	}
	//place breadth first
	if ( key[SDL_SCANCODE_Z] )
	{
		if ( m_previousEndNode != m_currentNode )//reset the previous node
		{
			m_Grid.at( m_previousEndNode )->setIsGoal( false );
			m_previousEndNode = m_currentNode;
		}
		//set the end to be the current node
		m_end->SetX( m_Grid.at( m_currentNode )->GetX() );
		m_end->SetY( m_Grid.at( m_currentNode )->GetY() );
		m_Grid.at( m_currentNode )->setIsGoal( true );
		//move breadth first agent to node
		m_breadthFirstData->SetEndNode( m_Grid.at( m_currentNode ) );
		m_breadthStateManager->AddState( new Idle( m_breadthStateManager, m_breadthFirstData ) );
	}
	//place best first
	if ( key[SDL_SCANCODE_X] )
	{
		if ( m_previousBestFirstNode != m_currentNode )//reset the previous node
		{
			m_Grid.at( m_previousBestFirstNode )->setIsGoal( false );
			m_previousBestFirstNode = m_currentNode;
		}
		//set the end to be the current node
		m_bestSprite->SetX( m_Grid.at( m_currentNode )->GetX() );
		m_bestSprite->SetY( m_Grid.at( m_currentNode )->GetY() );
		m_Grid.at( m_currentNode )->setIsGoal( true );
		//move breadth first agent to node
		m_bestFirstData->SetEndNode( m_Grid.at( m_currentNode ) );
		m_bestFirstManager->AddState( new Idle( m_bestFirstManager, m_bestFirstData ) );
	}
	//place A star
	if ( key[SDL_SCANCODE_C] )
	{
		if ( m_previousAStarNode != m_currentNode )//reset the previous node
		{
			m_Grid.at( m_previousAStarNode )->setIsGoal( false );
			m_previousAStarNode = m_currentNode;
		}
		//set the end to be the current node
		m_aStarSprite->SetX( m_Grid.at( m_currentNode )->GetX() );
		m_aStarSprite->SetY( m_Grid.at( m_currentNode )->GetY() );
		m_Grid.at( m_currentNode )->setIsGoal( true );
		//move breadth first agent to node
		m_aStarData->SetEndNode( m_Grid.at( m_currentNode ) );
		m_aStarManager->AddState( new Idle( m_aStarManager, m_aStarData ) );
	}

	if ( key[SDL_SCANCODE_BACKSPACE] )//clear grid if backspace is pressed
	{
		for each(Node* _node in m_Grid)
		{
			_node->setTexture( m_tile );
			_node->setMoveable( true );
		}
	}
	//walls
	if ( key[SDL_SCANCODE_1] )//if 1 is pressed set walls to be drawn
	{
		m_nodeCost = e_Wall;
	}
	if ( key[SDL_SCANCODE_2] )//if 2 is pressed set high cost nodes to be drawn
	{
		m_nodeCost = e_High;
	}
	if ( key[SDL_SCANCODE_3] )//if 3 is pressed set medium cost nodes to be drawn
	{
		m_nodeCost = e_Med;
	}
	if ( key[SDL_SCANCODE_4] )//if 4 is pressed set low cost nodes to be drawn
	{
		m_nodeCost = e_Low;
	}

	if ( SDL_GetMouseState( NULL, NULL ) && SDL_BUTTON( SDL_BUTTON_LEFT ) )
	{
		if ( key[SDL_SCANCODE_LCTRL] )//if control is held erase drawing
		{
			m_Grid.at( m_currentNode )->setTexture( m_tile );
			m_Grid.at( m_currentNode )->SetNodeCost( 0 );
			m_Grid.at( m_currentNode )->setMoveable( true );

		}
		else//else draw walls/costed nodes
		{
			switch ( m_nodeCost )
			{
			case(e_Wall):
			{
				m_Grid.at( m_currentNode )->setTexture( m_Wall );
				m_Grid.at( m_currentNode )->setMoveable( false );
				break;
			}
			case(e_High):
			{
				m_Grid.at( m_currentNode )->setTexture( m_HighCost );
				m_Grid.at( m_currentNode )->SetNodeCost( 6 );
				m_Grid.at( m_currentNode )->setMoveable( true );
				break;
			}
			case(e_Med):
			{
				m_Grid.at( m_currentNode )->setTexture( m_MedCost );
				m_Grid.at( m_currentNode )->SetNodeCost( 4 );
				m_Grid.at( m_currentNode )->setMoveable( true );
				break;
			}
			case(e_Low):
			{
				m_Grid.at( m_currentNode )->setTexture( m_LowCost );
				m_Grid.at( m_currentNode )->SetNodeCost( 2 );
				m_Grid.at( m_currentNode )->setMoveable( true );
				break;
			}
			}
		}
	}

	if ( key[SDL_SCANCODE_RETURN] )//if enter is presssed
	{
		if ( m_breadthStateManager->GetSizeOfStateVector() != 0 && m_aStarManager->GetSizeOfStateVector() != 0 && m_bestFirstManager->GetSizeOfStateVector() != 0 && m_StartNode != nullptr )//if all agents have been placed
		{
			m_stateManager->ChangeState( new InGame( m_stateManager, m_Grid, m_breadthStateManager, m_bestFirstManager, m_aStarManager, m_renderer, m_player ) );//change the state to in game
		}
	}
}

void SetUp::Draw()
{
	for ( size_t i = 0; i < m_Grid.size(); i++ )//draw grid
	{
		m_Grid.at( i )->Draw();
	}
	m_Select->Draw();//draw cursour
	m_end->Draw();//draw breadth first agent
	m_bestSprite->Draw();//draw best first agent
	m_aStarSprite->Draw();//draw a star agent
	m_player->Draw();//draw player
}